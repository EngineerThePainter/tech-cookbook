def my_decorator(func):
    def wrapper():
        print("This is before calling the function")
        func()
        print("This is after calling the function")
    return wrapper


@my_decorator
def say_whee():
    print("WHEEEEEEEEEEEEEEEEEEEEE")


say_whee()
