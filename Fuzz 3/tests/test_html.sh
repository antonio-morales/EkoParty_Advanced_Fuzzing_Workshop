#! /bin/sh

result=0

for name in ${srcdir}/*.rtf; do

    output=`echo ${name} | sed "sI.\+/IIg"`
    echo "${UNRTF} ${name} > ${output}.html"

    if ${UNRTF} ${name} > ${output}.html; then
	echo "success."
    else
	echo "FAILURE!"
	result=1
    fi
done

exit $result
