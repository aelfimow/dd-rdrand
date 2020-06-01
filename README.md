# dd-rdrand
`dd` using `RDRAND` instruction of x86 CPUs.

## Usage
```
dd_rand of=<file> bs=<block size> count=<number of blocks>
```

Arguments:
* `of`: output file
* `bs`: block size (in bytes)
* `count`: number of blocks

Example creating a file `a.bin` filled with random numbers total of 2048 bytes:
```
dd_rand of=a.bin bs=1024 count=2
```

## Note
The assembly functions have been generated in [rdrand-measurement-gen](https://github.com/aelfimow/rdrand-measurement-gen).
