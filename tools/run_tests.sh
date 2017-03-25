for test_file in build/*
do
    echo "============$test_file============"
    ./"$test_file"
    echo ""
done


