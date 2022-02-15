test_dir="hw04"
cd 1st/${test_dir}
make

function execute(){
    echo ""
    echo "========================"
    ./$1
    echo "========================"
}

for file in $(ls | grep ^[^.]*$ | grep ^[^Makefile]); do
    execute $file
done

# make clean