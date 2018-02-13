from collections import OrderedDict

DELIM = "\t"

def slug(s):
    """
    Generates a slug of the string `s`
    """
    return s.replace(" ", "_")


def num_tests(cases):
    """
    Returns the number of test cases in `cases`
    """
    sum = 0

    for k, v in cases.items():
        sum += len(v)

    return sum

def read_test_manifest(path, generate_default_cases=True):
    """
    Reads a unit test manifest from the manifest file at `path`. Returns a
    dictionary with unit names as keys and lists of test cases as values.
    """
    test_cases = OrderedDict()
    current_unit = ""
    first_line = True

    with open(path) as file:
        for line in file.readlines():
            
            if first_line: # read module name
                module_name = line.strip()
                first_line = False
                continue

            if line[0] == DELIM: # new test case
                test_cases[current_unit].append(line[1:].strip())
            elif line[0] != '\n': # new unit
                current_unit = line.strip()
                test_cases[current_unit] = []
            else: # skip blank lines
                continue

    # generate default test cases for each unit (if enabled)
    if generate_default_cases:
        for k in test_cases.keys():
            test_cases[k].insert(0, "null params")
            test_cases[k].insert(0, "normal")

    # remove blank lines from dictionary
    if '' in test_cases.keys():
        test_cases.pop('')

    return (module_name, test_cases)

def generate_test_stub_headers(module_name, cases):
    """
    Produces function declarations for test cases in C syntax
    """
    s = ""

    # includes
    s += "#include <stdbool.h>\n"
    s += "\n"

    s += "#define UNIT_{0}_NUM_TESTS {1}\n".format(module_name.swapcase(),
            num_tests(cases))
    s+= "\n"

    # generate function headers for each test case
    for k, v in cases.items():
        unit_name = k

        for case in v:
            s += "bool test_{0}_{1}_{2}(void);\n".format(module_name, unit_name,
                    slug(case))

        s += "\n"

    return s

def generate_test_stub_bodies(module_name, cases):
    """
    Produces blank templates for test cases in C syntax
    """
    s = ""

    # includes
    s += "#include <stdbool.h>\n"
    s += "\n"
    s += "#include \"unit_{0}.h\"\n".format(module_name)
    s += "\n"

    # generate function body for each test case
    for k, v in cases.items():
        unit_name = k

        for case in v:
            s += "bool {0}_{1}_{2}(void)\n".format(module_name, unit_name,
                slug(case))
            s += "{\n"
            s += " "*4 + "bool pass = false;\n"
            s += "\n"
            s += " "*4 + "/* logic here */\n"
            s += "\n"
            s += " "*4 + "if(/* condition here */)\n"
            s += " "*4 + "{\n"
            s += " "*8 + "pass = true;\n"
            s += " "*4 + "}\n"
            s += "\n"
            s += " "*4 + "return pass;\n"
            s += "}\n"
            s+= "\n"

    return s

def generate_test_runner(module_name, cases):
    """
    Produces actual test execution code in C syntax
    """
    s = ""

    # includes
    s += "#include <stdio.h>\n"
    s += "#include <stdlib.h>\n"
    s += "\n"
    s += "#include \"unit_{0}.h\"\n".format(module_name)
    s += "\n"

    # test name strings
    s += "/* test names */\n"
    s += "const char* tests[UNIT_{0}_NUM_TESTS] = {{\n".format(module_name.swapcase())

    for k, v in cases.items():
        unit_name = k

        for case in v:
            s += " "*4 + "\"test_{0}_{1}_{2}\",\n".format(module_name,
                unit_name, slug(case))

    s += "}\n"
    s += "\n"

    # main() body
    s += "int main(void)\n"
    s += "{\n"
    s += " "*4 + "unsigned int t = 0;\n"
    s += " "*4 + "bool results[UNIT_{0}_NUM_TESTS];\n".format(
        module_name.swapcase())
    s += " "*4 + "memset(results, 0, sizeof(bool) * UNIT_{0}_NUM_TESTS);\n".format(module_name.swapcase())
    s += "\n"

    for k, v in cases.items():
        unit_name = k

        for case in v:
            s += " "*4 + "results[t] = test_{0}_{1}_{2}();\n".format(
                module_name, unit_name, case)
            s += " "*4 + "t++;\n"

        s += "\n"

    s += " "*4 + "/* check for test failure */\n"
    s += " "*4 + "for(unsigned int i=0;i<t;i++)\n"
    s += " "*4 + "{\n"
    s += " "*8 + "if(results[i])\n"
    s += " "*8 + "{\n"
    s += " "*12 + "printf(\"TEST %s: PASS\\n\", tests[i]);\n"
    s += " "*8 + "}\n"
    s += " "*8 + "else\n"
    s += " "*8 + "{\n"
    s += " "*12 + "printf(\"!TEST %s: FAIL\\n\", tests[i]);\n"
    s += " "*8 + "}\n"
    s += " "*4 + "}\n"

    s += " "*4 + "return EXIT_SUCCESS;\n"
    s += "}\n"

    return s

import sys

if __name__ == "__main__":
    if len(sys.argv) != 3: # usage
        print("usage: python3 tools/test_scaffold.py path/to/manifest/file /path/to/output\n")
        exit(1)

    manifest_file_path = sys.argv[1]
    output_path = sys.argv[2]

    (module_name, test_cases) = read_test_manifest(manifest_file_path)

    # generate code
    test_headers = generate_test_stub_headers(module_name, test_cases)
    test_bodies = generate_test_stub_bodies(module_name, test_cases)
    test_runner = generate_test_runner(module_name, test_cases)

    # write code to relevant files
    with open(output_path + "/unit_{0}.h".format(module_name), "w+") as decl_file:
        decl_file.write(test_headers)

    with open(output_path + "/unit_{0}.c".format(module_name), "w+") as defn_file:
        defn_file.write(test_bodies)

    with open(output_path + "/test_{0}.c".format(module_name), "w+") as main_file:
        main_file.write(test_runner)

