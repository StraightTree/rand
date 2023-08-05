# rand
An awesome random generator for the terminal.

# Outline
A more detailed description can be found on the wiki-page.
The basic idea is to create a versatile random generator for the terminal.

## Supported commands:
```
-h ... Print help text
-r a b ... choose a random number in range (a, b) (a,b inclusive)
-s... create a random string
-s f ... create a random string with flags. f can be a combination from s=special character, n=numbers, u=upper case l=lower case
-l k ... result should have k character/digits
```

### Examples
Create a random string containing numbers and upper-case letters.
```
./rand -s nu -l 20
> 3SB9JBIPAW24M46AXS9P
```

Choose a random number between 0 and 9999
```
./rand -r 0 9999
> 634
```

### Detailed description
#### Random number
In order to generate random numbers, the argument `-r` or `-random` can be used. This argument supports the
following parameter:
- `-r` ... generates a random number in range `(0, std::numeric_limits<ssize_t>::max())`
- `-r k` ... generates a random number in range `(0, k)`
- `-r l k` ... generates a random number in range `(l, k)`

The flag `-l` or `-length` in combination with `-r` is not supported and has therefore no effect. To limit the length
of the output, adjust the lower- / upper-bound accordingly.

#### Random string
In order to generate a random string, the argument `-s` or `-string` can be used. This argument supports the
following parameter:
- `-s` ... generates a random string with the default length (20 character)
- `-s k` ... generates a random string using only a certain character set. `k` can be any combination of 
`n` numeric, `u` upper-case character, `l` lower-case character, `s` special character. Note that each flag can 
specified zero or one time. Specifying a single flag multiple times leads to an error.

String generation also supports the argument `-l` or `-length` to set the exact length of the output string. 
The argument is 
used as follows: `-l k`, where `k` is a natual number larger than 0

## Collaboration
For feature requests / ideas please create a new issue or open a pull requst.

## Note:
The numbers generated by this tool are only *pseudo random*, hence be careful what you use them for.
