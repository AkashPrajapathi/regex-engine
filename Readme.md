# 🔥 RegEx Engine — Build Your Own Regular Expression Engine from Scratch

A **C++ implementation of a classic regex engine** built from first principles — from **AST → NFA → Simulation** using **Thompson’s construction algorithm**.  

This project mimics the **textbook style regex engine** taught in compiler design and automata theory — clean, deterministic, and theory-accurate.

---

## 🚀 Features

✅ Converts regular expressions into an **Abstract Syntax Tree (AST)**  
✅ Implements **Thompson’s Construction Algorithm** to build ε-NFA  
✅ Simulates NFA using **ε-closure** and **move** operations  
✅ Supports all core regex operators:

| Operator | Meaning     | Example              |
|----------|-------------|----------------------|
| `*`      | Kleene star | `a*` → 0 or more `a` |
| `+`      | One or more | `a+`                 |
| `?`      | Zero or one | `a?`                 |
| `\|`     | Alternation | `a\|b`               |
| `()`     | Grouping    | `(a\|b)c`            |

---

## 🧠 Theory Summary

The engine follows the **classical flow**:


Each operator expands to a small NFA fragment.  
The final NFA is simulated nondeterministically via `ε-closure` and `move()` functions.

---

## 💡 Example

```cpp
#include "parser.hpp"
#include "nfa.hpp"

int main() {
    std::string pattern = "(a|b)*abb";
    std::string test = "aabb";

    re::Lexer lex(pattern);
    re::Parser parser(lex);
    auto ast = parser.parse();

    re::nfa::NFA nfa(ast);
    bool matched = nfa.simulateNFA(test);

    std::cout << (matched ? "Matched ✅" : "Not matched ❌") << std::endl;
}
```

## 🧭 Roadmap

- [ ] 🧩 Add **Character classes** — `[a-z]`, `[0-9]`
- [ ] 🔤 Add **Escape sequences** — `\n`, `\t`, `\s`
- [ ] ⛓️ Support **Anchors** — `^` (start), `$` (end)
- [ ] ⚡ Implement **NFA → DFA conversion**
- [ ] 🧱 Add **NFA graph visualization**
- [ ] 🧪 Benchmark vs **backtracking regex engines**

## 🏆 Victory Checklist

![Progress](https://img.shields.io/badge/Progress-Core%20Engine%20Done-brightgreen)
![Speed](https://img.shields.io/badge/Time-2.5%20days-blue)
![Status](https://img.shields.io/badge/Status-Shiny%20Ready-yellow)

- [x] **Core RegEx Engine completed** — finished in **2.5 days** ⚡
- [ ] Additional features / optimizations (coming soon) ✨
- [ ] Documentation and examples 📚
- [ ] Tests and edge cases ✅

**Status:** Shiny and ready! 🎉
