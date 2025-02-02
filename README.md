# tokenizer

A usable tokenizer written in C. It's simple, and gets the job done. No claims about super fast performance or any of that cool hip stuff that most of these READMEs have. 

You can just use it like this:

## Build
```bash
zig build
```

Binaries get dumped into `zig-out`.

## Run
Usage is straightforward. Only 2 args needed:
1. The file you want to tokenize. Anything that is text and readable by the eye.
2. A string containing all the characters you want to use as delimeters.

```bash
./tokenizer path/to/file.txt " .?!"
```

## Example

If you had a string: `hello, world! I am home! it is a great day.` with the delimeters ` ,.!`, then the output looks like this:

```
hello
,

world
!

I

am

home
!

it

is

a

great

day
.
```

Note that we keep the delimiters. Up to you to filter that out separately.

Enjoy!