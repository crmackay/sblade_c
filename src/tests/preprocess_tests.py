#!/usr/bin/env python3
import os


# for each files

# open file --> read line by line -->
#   find function names that look like "int test_"

# collect fn names

# put them into a main function, in the manner in which then will run

# TODO: add this script to makefile to file before sending c source files to compiler

# find test function
def findTestFnNames(lines):
    names = []
    for line in lines:
        if line.startswith("int test_"):
            # print(line.index("("))
            names.append((line[4:line.index("(")]))
    return(names)

# finds the index for the line with the main function in the array of lines pass in
def findMainFn(lines):
    idx = 0
    for i, line in enumerate(lines):
        if line.startswith("int main("):
            idx = i

    if idx == 0:
        idx = len(lines)
    return(idx)

def replaceMainFn(lines, iMain, insert):
    print(iMain)
    r = lines[0:iMain]
    # print(r)
    toAdd = ["int main(void){\n"]
    for fn in insert:
        toAdd.append(fn)
    toAdd.append("}")
    # print("".join(toAdd))
    r += toAdd

    return(r)

def fnNamesToInserts(names):
    inserts = []
    for name in names:
        # run_test(test_new_int_matrix, "test_new_int_matrix");
        newfn = '\t'+'run_test(' + name + ', "' + name + '");\n'
        inserts.append(newfn)
    return(inserts)

def main():
    print("prepping tests...")
    filesToProcess = []

    for dirpath, dirnames, filenames in os.walk("./tests"):
        for file in filenames:
            if file.endswith("_test.c"):
                filesToProcess.append(os.path.join(dirpath, file))

    print("processing files:")
    print (filesToProcess)

    for file in filesToProcess:
        lines = []
        print(file)
        with open(file, mode="r", encoding='utf-8') as open_file:
            lines = open_file.readlines()
        fnNames = findTestFnNames(lines)
        i = findMainFn(lines)
        inserts = fnNamesToInserts(fnNames)
        # print("".join(inserts))
        r = replaceMainFn(lines, i, inserts)
        # print("".join(r))
        with open(file+"_1", mode="w", encoding='utf-8') as open_file:
            open_file.write("".join(r))



if __name__ == "__main__":
    main()
