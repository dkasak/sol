NOTICE="Copyright 2011, 2012 Denis Kasak <dkasak[at]termina.org.uk>"
echo "$(sed -e 's/Foobar/Sol/g' ~/docs/gpl-statement.txt)" > notice.tmp


for file in *.{c,h,cpp}
do
    touch $file.tmp
    exec 3>$file.tmp
    echo "/**" >&3
    echo -n " * " >&3
    echo $NOTICE >&3
    echo " * " >&3
    while read line;
    do
        echo -n " * " >&3
        echo $line >&3
    done < notice.tmp
    echo " */" >&3
    echo >&3
    cat $file >&3
    exec 3<&-
    mv $file.tmp $file
done

rm notice.tmp
