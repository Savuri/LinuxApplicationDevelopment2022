set pagination off

b 32 if cur % 5 == 0
command 1
    printf "@@@ start=%ld end=%ld step=%ld cur=%ld\n", start, end, step, cur
    c
end
r
q