const assert = (truth, message) => {
    if (!truth) {
        throw new Error(message)
    }
}
const { hasOwn } = Object

function get(
    obj,
    key,
    defaultValue,
) {
    if (hasOwn(obj, key)) {
        return obj[key]
    } else {
        return defaultValue
    }
}

function getForce(obj, key) {
    const v = get(obj, key)
    assert(v != null)
    return v
}

function isNumber(x) {
    if (typeof x === "number") return true
    if (/^0x[0-9a-f]+$/i.test(String(x))) return true
    return /^[-+]?(?:\d+(?:\.\d*)?|\.\d+)(e[-+]?\d+)?$/.test(String(x))
}

function hasKey(obj, keys) {
    let o = obj
    keys.slice(0, -1).forEach((key) => {
        o = (get(o, key) ?? {})
    })

    const key = keys[keys.length - 1]
    return hasOwn(o, key)
}

/** Take a set of command line arguments, optionally with a set of options, and
 * return an object representing the flags found in the passed arguments.
 *
 * By default, any arguments starting with `-` or `--` are considered boolean
 * flags. If the argument name is followed by an equal sign (`=`) it is
 * considered a key-value pair. Any arguments which could not be parsed are
 * available in the `_` property of the returned object.
 *
 * By default, the flags module tries to determine the type of all arguments
 * automatically and the return type of the `parse` method will have an index
 * signature with `any` as value (`{ [x: string]: any }`).
 *
 * If the `string`, `boolean` or `collect` option is set, the return value of
 * the `parse` method will be fully typed and the index signature of the return
 * type will change to `{ [x: string]: unknown }`.
 *
 * Any arguments after `'--'` will not be parsed and will end up in `parsedArgs._`.
 *
 * Numeric-looking arguments will be returned as numbers unless `options.string`
 * or `options.boolean` is set for that argument name.
 *
 * @example
 * ```ts
 * import { Args } from "../support/parse_args.js"
 * const parsedArgs = new Args({argList: Deno.args})
 * ```
 *
 * @example
 * ```ts
 * import { Args } from "../support/parse_args.js"
 * const parsedArgs = Args({argList:["--foo", "--bar=baz", "./quux.txt"]})
 * // parsedArgs: { foo: true, bar: "baz", _: ["./quux.txt"] }
 * ```
 */
export class Args {
    constructor({
        argList,
        alias = {},
        boolean = false,
        stopEarly = false,
        string = [],
        collect = [],
        negatable = [],
        unknown = (i) => i,
        ...otherArgs
    }) {
        this.argList = argList

        const doubleDash = Object.keys(otherArgs).includes("--")
        const defaults = get(otherArgs, "default", {})
        const aliases = {}
        const flags = {
            bools: {},
            strings: {},
            unknownFn: unknown,
            allBools: false,
            collect: {},
            negatable: {},
        }
        const nonFlagArgs = []

        if (alias !== undefined) {
            for (const key in alias) {
                const val = getForce(alias, key)
                if (typeof val === "string") {
                    aliases[key] = [val]
                } else {
                    aliases[key] = val
                }
                for (const alias of getForce(aliases, key)) {
                    aliases[alias] = [key].concat(aliases[key].filter((y) => alias !== y))
                }
            }
        }

        if (boolean !== undefined) {
            if (typeof boolean === "boolean") {
                flags.allBools = !!boolean
            } else {
                const booleanArgs = typeof boolean === "string"
                    ? [boolean]
                    : boolean

                for (const key of booleanArgs.filter(Boolean)) {
                    flags.bools[key] = true
                    const alias = get(aliases, key)
                    if (alias) {
                        for (const al of alias) {
                            flags.bools[al] = true
                        }
                    }
                }
            }
        }

        if (string !== undefined) {
            const stringArgs = typeof string === "string"
                ? [string]
                : string

            for (const key of stringArgs.filter(Boolean)) {
                flags.strings[key] = true
                const alias = get(aliases, key)
                if (alias) {
                    for (const al of alias) {
                        flags.strings[al] = true
                    }
                }
            }
        }

        if (collect !== undefined) {
            const collectArgs = typeof collect === "string"
                ? [collect]
                : collect

            for (const key of collectArgs.filter(Boolean)) {
                flags.collect[key] = true
                const alias = get(aliases, key)
                if (alias) {
                    for (const al of alias) {
                        flags.collect[al] = true
                    }
                }
            }
        }

        if (negatable !== undefined) {
            const negatableArgs = typeof negatable === "string"
                ? [negatable]
                : negatable

            for (const key of negatableArgs.filter(Boolean)) {
                flags.negatable[key] = true
                const alias = get(aliases, key)
                if (alias) {
                    for (const al of alias) {
                        flags.negatable[al] = true
                    }
                }
            }
        }

        const argv = {}

        function argDefined(key, arg) {
            return (
                (flags.allBools && /^--[^=]+$/.test(arg)) ||
                get(flags.bools, key) ||
                !!get(flags.strings, key) ||
                !!get(aliases, key)
            )
        }

        function setKey(
            obj,
            name,
            value,
            collect = true,
        ) {
            let o = obj
            const keys = name.split(".")
            keys.slice(0, -1).forEach(function (key) {
                if (get(o, key) === undefined) {
                    o[key] = {}
                }
                o = get(o, key)
            })

            const key = keys[keys.length - 1]
            const collectable = collect && !!get(flags.collect, name)

            if (!collectable) {
                o[key] = value
            } else if (get(o, key) === undefined) {
                o[key] = [value]
            } else if (Array.isArray(get(o, key))) {
                (o[key]).push(value)
            } else {
                o[key] = [get(o, key), value]
            }
        }

        function setArg(
            key,
            val,
            arg,
            collect,
        ) {
            if (arg && flags.unknownFn && !argDefined(key, arg)) {
                if (flags.unknownFn(arg, key, val) === false) return
            }

            const value = !get(flags.strings, key) && isNumber(val) ? Number(val) : val
            setKey(argv, key, value, collect)

            const alias = get(aliases, key)
            if (alias) {
                for (const x of alias) {
                    setKey(argv, x, value, collect)
                }
            }
        }

        function aliasIsBoolean(key) {
            return getForce(aliases, key).some(
                (x) => typeof get(flags.bools, x) === "boolean",
            )
        }

        let notFlags = []
        let args = argList
        
        // all args after "--" are not parsed
        if (args.includes("--")) {
            notFlags = args.slice(args.indexOf("--") + 1)
            args = args.slice(0, args.indexOf("--"))
        }

        for (let i = 0; i < args.length; i++) {
            const arg = args[i]

            if (/^--.+=/.test(arg)) {
                const m = arg.match(/^--([^=]+)=(.*)$/s)
                assert(m != null)
                const [, key, value] = m

                if (flags.bools[key]) {
                    const booleanValue = value !== "false"
                    setArg(key, booleanValue, arg)
                } else {
                    setArg(key, value, arg)
                }
            } else if (
                /^--no-.+/.test(arg) && get(flags.negatable, arg.replace(/^--no-/, ""))
            ) {
                const m = arg.match(/^--no-(.+)/)
                assert(m != null)
                setArg(m[1], false, arg, false)
            } else if (/^--.+/.test(arg)) {
                const m = arg.match(/^--(.+)/)
                assert(m != null)
                const [, key] = m
                const next = args[i + 1]
                if (
                    next !== undefined &&
                    !/^-/.test(next) &&
                    !get(flags.bools, key) &&
                    !flags.allBools &&
                    (get(aliases, key) ? !aliasIsBoolean(key) : true)
                ) {
                    setArg(key, next, arg)
                    i++
                } else if (/^(true|false)$/.test(next)) {
                    setArg(key, next === "true", arg)
                    i++
                } else {
                    setArg(key, get(flags.strings, key) ? "" : true, arg)
                }
            } else if (/^-[^-]+/.test(arg)) {
                const letters = arg.slice(1, -1).split("")

                let broken = false
                for (let j = 0; j < letters.length; j++) {
                    const next = arg.slice(j + 2)

                    if (next === "-") {
                        setArg(letters[j], next, arg)
                        continue
                    }

                    if (/[A-Za-z]/.test(letters[j]) && /=/.test(next)) {
                        setArg(letters[j], next.split(/=(.+)/)[1], arg)
                        broken = true
                        break
                    }

                    if (
                        /[A-Za-z]/.test(letters[j]) &&
                        /-?\d+(\.\d*)?(e-?\d+)?$/.test(next)
                    ) {
                        setArg(letters[j], next, arg)
                        broken = true
                        break
                    }

                    if (letters[j + 1] && letters[j + 1].match(/\W/)) {
                        setArg(letters[j], arg.slice(j + 2), arg)
                        broken = true
                        break
                    } else {
                        setArg(letters[j], get(flags.strings, letters[j]) ? "" : true, arg)
                    }
                }

                const [key] = arg.slice(-1)
                if (!broken && key !== "-") {
                    if (
                        args[i + 1] &&
                        !/^(-|--)[^-]/.test(args[i + 1]) &&
                        !get(flags.bools, key) &&
                        (get(aliases, key) ? !aliasIsBoolean(key) : true)
                    ) {
                        setArg(key, args[i + 1], arg)
                        i++
                    } else if (args[i + 1] && /^(true|false)$/.test(args[i + 1])) {
                        setArg(key, args[i + 1] === "true", arg)
                        i++
                    } else {
                        setArg(key, get(flags.strings, key) ? "" : true, arg)
                    }
                }
            } else {
                if (!flags.unknownFn || flags.unknownFn(arg) !== false) {
                    nonFlagArgs.push(flags.strings["_"] ?? !isNumber(arg) ? arg : Number(arg))
                }
                if (stopEarly) {
                    nonFlagArgs.push(...args.slice(i + 1))
                    break
                }
            }
        }

        for (const [key, value] of Object.entries(defaults)) {
            if (!hasKey(argv, key.split("."))) {
                setKey(argv, key, value, false)

                if (aliases[key]) {
                    for (const x of aliases[key]) {
                        setKey(argv, x, value, false)
                    }
                }
            }
        }

        for (const key of Object.keys(flags.bools)) {
            if (!hasKey(argv, key.split("."))) {
                const value = get(flags.collect, key) ? [] : false
                setKey(
                    argv,
                    key,
                    value,
                    false,
                )
            }
        }

        for (const key of Object.keys(flags.strings)) {
            if (!hasKey(argv, key.split(".")) && get(flags.collect, key)) {
                setKey(
                    argv,
                    key,
                    [],
                    false,
                )
            }
        }

        if (doubleDash) {
            argv["--"] = []
            for (const key of notFlags) {
                argv["--"].push(key)
            }
        } else {
            for (const key of notFlags) {
                nonFlagArgs.push(key)
            }
        }
        
        this.nonFlagArgs = nonFlagArgs
        this.namedArgs = argv
        this.flags = flags
        this.names = Object.keys(argv)
    }

    includesAllNames(...names) {
        return names.every(name=>this.names.includes(name))
    }

    argListAfterReplacements(keyValues) {
        const newArgList = []
        const keysToReplace = Object.keys(keyValues)
        const booleanFlagNames = Object.keys(this.flags.bools)
        let skipNextValue = false
        for (const [current, next] of this.argList.map((each, index)=>[each,this.argList[(index-0)+1]])) {
            if (skipNextValue) {
                skipNextValue = false
                continue
            }
            if (current == "--") {
                break
            }
            const isFlag = current.startsWith("--")
            const flagName = current.slice(2)
            const isBooleanFlag = isFlag && booleanFlagNames.includes(flagName)
            const nextIsFlag = next && next.startsWith("--")
            const needsReplacing = keysToReplace.includes(flagName)
            if (!isFlag) {
                newArgList.push(current)
            } else if (isBooleanFlag) {
                newArgList.push(current)
                if (!needsReplacing) {
                    newArgList.push(next)
                    skipNextValue = true
                // if needs replacing
                } else {
                    if (newArgList[flagName]) {
                        newArgList.push("true")
                    } else {
                        newArgList.push("false")
                    }
                    if (!nextIsFlag) {
                        skipNextValue = true
                    }
                }
            } else {
                // edgecase, something is broken (named-arg but no value given for name)
                if (next === undefined) {
                    newArgList.push(current)
                // keep as-is
                } else if (!needsReplacing) {
                    newArgList.push(current)
                    newArgList.push(next)
                    skipNextValue = true
                // replace
                } else {
                    newArgList.push(current)
                    newArgList.push(`${keyValues[flagName]}`)
                    skipNextValue = true
                }
            }
        }
        return newArgList
    }
}