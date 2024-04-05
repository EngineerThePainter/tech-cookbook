My slightly changed version of codes from "Cpp Concurrency in Action" by Anthony Williams.

Protip: to run them effectively use:

```
valgrind -s --tool=helgrind <program>
```

Thread sanitizer caused a lot of false positives (at least on one of my machines).