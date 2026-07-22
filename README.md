# Guess the Number

> A simple terminal number guessing game written in C. > 

In this game the computer picks a random number for you to guess. You can choose one of three ranked levels, which are automatically saved in a local text file, or you can choose a non-ranked custom level for you to challange yourself with bigger ranges. 

### Features

- 3 Game levels
	- Easy `1-10`
	- Medium `1-100`
	- Hard `1-1000`
- Custom mode with your own max range
- Counting the number of attempts
- Saving best score

### Menu

```
=====================
 Guess the Number
=====================
1. Easy
2. Medium
3. Hard
4. Custom
5. Check max score
6. Exit
```

### Score system

Less attempts, better score!

For example:

```
5 easy
12 medium
20 hard
```

### What I've learned and what I want to add next

This project taught me:
- Use `bool` instead of `1` or `0`
- in `limits.h` there is `EXIT_SUCCESS` and `INT_MAX` etc.
- A lot of basics things about working with files
- Comparing strings using `strcmp()`

What I want to add next:
- Add leaderboard with usernames
- Better score management
- Maybe a bit optimized code
- GUI (i doubt it), or just prettier looking terminal
- Reduce some bugs, corrupt files handling
- Make it more user-friendly

### Compilation

You can compile the game using GCC:

`gcc 'Guess The Number.c' -o 'Guess The Number'`

Then run it with:

`./guess`

On Windows:

`guess.exe`

The game uses only the standard C library, so no additional dependencies are required.
