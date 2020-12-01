from invoke import task, run
from invoke.exceptions import UnexpectedExit

@task()
def build_math_calc(c):
    """ Build the shared library for the sample C++ code """

    try:
        run("mkdir MathCalc/build")
    except UnexpectedExit as identifier:
        print(f"cannot create a directory: {identifier}")
    
    run("cmake -B MathCalc/build MathCalc/")
    run("cmake --build MathCalc/build")
    run("cp MathCalc/build/libMathCalc.so .")
    print("* Complete")


@task(
    build_math_calc
)
def all(c):
    """ Build and run all tests """
    build_math_calc(c)
    pass