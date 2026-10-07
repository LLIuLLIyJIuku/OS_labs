# Lab 4 — Processes & Threads

| Exercise | Files | Description |
|---|---|---|
| 1 | `ex1.c`, `ex1.sh` | Main process creates two children (both children of main), prints PID/PPID and execution time in ms |
| 2 | `ex2.c`, `ex2.sh`, `ex2.txt` | `fork()` in a loop `n` times (n from command line), observed with `pstree`; explanation in `ex2.txt` |
| 3 | `ex3.c`, `ex3.sh` | Simple shell: runs commands with arguments in background via `fork` + `exec` (no `system`) |

Run on Linux:

```bash
bash ex1.sh
bash ex2.sh
bash ex3.sh
```

Example for the shell (`ex3`):

```
myshell> ls -l
[1234] started in background
myshell> pstree -p
myshell> exit
```
