set pagination off

set $i = 0
b 32
ignore 1 27
command 1
    printf "@@@ start=%ld end=%ld step=%ld cur=%ld\n", start, end, step, cur

    if ($i++ == 7)
       d 1
    end

    c
end
r
q