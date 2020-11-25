from invoke import task, run

# def print_banner(msg):
#     print("==================================================")
#     print("= {} ".format(msg)

@task()
def build_math_calc(c):
    """ Build the shared library for the sample C++ code """
    # print_banner("Building C++ Library")

    # run("mkdir build")
    run("cmake -B build")
    run("cmake --build build")
    run("cp build/libMathCalc.so .")
    print("* Complete")


@task(
    build_math_calc
)
def all(c):
    """ Build and run all tests """
    pass