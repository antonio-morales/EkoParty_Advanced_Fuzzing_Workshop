#! /bin/sh

result=0

for name in ${srcdir}/*.rtf; do

    output=`echo ${name} | sed "sI.\+/IIg"`
    echo "${UNRTF} --latex ${name} > ${output}.tex"

    if ${UNRTF} --latex ${name} > ${output}.tex; then
	echo "success."
    else
	echo "FAILURE!"
	result=1
    fi
done

exit $result

