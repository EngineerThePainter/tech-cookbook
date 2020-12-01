from invoke import task, run
from invoke.exceptions import UnexpectedExit

@task()
def build_pybind(c):
    """ Build the shared library for the sample C++ code """

    try:
        run("mkdir Shapes/build")
    except UnexpectedExit as identifier:
        print(f"cannot create a directory: {identifier}")
    run("conan install -if Shapes/build Shapes")
    run("cmake -B Shapes/build Shapes/")
    run("cmake --build Shapes/build")
    run("cp Shapes/build/lib/Shapes.cpython-38-x86_64-linux-gnu.so .")
    print("* Complete")


@task(
    build_pybind
)
def all(c):
    """ Build and run all tests """
    build_pybind(c)
    pass