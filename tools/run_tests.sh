for test_file in build/*
do
    if [ "$test_file" != "build/libjcrl.a" ]
    then
        echo "============$test_file============"
        ./"$test_file"
        echo ""
    fi
done


