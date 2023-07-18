from decorators import do_twice
from decorators import do_twice_with_args
from decorators import do_twice_and_return_second_time


@do_twice
def say_whee():
    print("WHEEEEE")


say_whee()


@do_twice_with_args
def greet(name):
    print(f"Hello {name}")


greet("Bob")


@do_twice_and_return_second_time
def greet_return(name):
    print("Preparing")
    return f"Hello {name}"


print(greet_return("Bob"))