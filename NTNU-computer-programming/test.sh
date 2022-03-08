test_dir="hw01"
cd 2nd/${test_dir}
testfiles=$(cat testcase)
make

# function execute(){
#     for testcase in $testfiles; do
#         echo $testcase
#         echo ""
#         echo "========================"
#         ./$1 < testcase
#         echo "========================"
#     done
# }

# for file in $(ls | grep ^[^.]*$ | grep ^[^Makefile] | grep ^[^testcase]); do
#     execute $file
# done

# make clean