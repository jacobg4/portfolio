# Project Source Archive

Full source for the coursework and personal projects referenced on the portfolio site
(excerpts of these same files are shown in-browser via the "View Source" buttons on
[the live site](../index.html)). Compiled binaries (`.exe`) and assignment write-up PDFs
are omitted; only source code and the data files needed to run it are included.

Blood & Burden's full source is intentionally **not** included — `blood-burden-architecture-sample/`
has a curated, secret-free excerpt instead. See that folder's own README for why.

| Folder | Description |
|---|---|
| `blackjack-casino-engine/` | CS317 blackjack coursework. `GivhanProj2.cpp` is the original monolithic version; `GivhanBonusProject.cpp` is the refactor into functions with betting, dealer AI, and file-based hand history. |
| `movie-theater-reservation/` | CS317 seat-map ticketing system, plus a sample run transcript (`GivhanProj3.txt`). |
| `sudoku-generator/` | Two Sudoku generation approaches: a general N&times;N recursive backtracking solver, and a 4&times;4 block-shuffle generator with timing. |
| `tiny-rpg/` | A data-driven Python CLI RPG — the direct predecessor to Blood & Burden. Monsters, dungeons, quests, and items are all defined in the JSON files here; `save_data.example.json` is a sample save. |
| `rpg-prototype-cpp/` | The earliest prototype: a rough, unfinished C++ console RPG that came before tiny-rpg. |
| `python-utility-scripts/` | Small sysadmin/security practice scripts: file organizer, log analyzer, password strength checker, network scanner, and an educational Merkle-Hellman knapsack cipher (`merkle_hellman.py`). |
| `credit-payoff-planner/` | Python CLI that validates several credit cards and simulates month-by-month payoff under minimum-only (baseline), avalanche, snowball and highest-balance strategies with a fully rolled-over payment pool, then writes a side-by-side report and payoff timeline. `sample_report.txt` shows example output from made-up cards. |
| `blood-burden-architecture-sample/` | A curated, secret-free excerpt of Blood & Burden's PHP backend — architecture and code quality only, no game content or credentials. |
