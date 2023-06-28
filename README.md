# rand
An awesome random generator for the terminal **which is currently in the developing process.** Please watch this repository to get informed when the first release is available.

## Supported commands:
```
-h ... Print help text
-r a b ... choose a random number in range (a, b) (a,b inclusive)
-s... create a random string
-s f ... create a random string with flags. f can be a combination from s=special character, n=numbers, u=upper case l=lower case
-l k ... result should have k character/digits
-c a1,...,an, k ... choose k items from the list a1...an
-g a1,...an ... group n items in a random order
```

### Example
Create a random string containing numbers ad upper-case letters.
```
./rand -s nu -l 20
> 3SB9JBIPAW24M46AXS9P
```

Choose a random number between 0 and 9999 with 2 digits
```
./rand -r 0 9999 -l 2
> 63
```

Choose a random item from a list
```
./rand -c Alice Bob Tom
> Tom
```

Choose three random items from a list
```
./rand -c Alice Bob Tom, 3
> Tom
> Alice
> Tom
```

## Collaboration
For feature requests / ideas please create a new issue or open a pull requst.

## Note:
The numbers generated by this tool are only *pseudo random*, hence be careful what you use them for.
