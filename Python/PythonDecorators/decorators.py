import functools


def do_twice(func):
    # Now when introspection will be used the passed function will not be that confused with the decorator information
    @functools.wraps(func)
    def wrapper_do_twice():
        func()
        func()
    return wrapper_do_twice


def do_twice_with_args(func):
    def wrapper_do_twice(*args, **kwargs):
        func(*args, **kwargs)
        func(*args, **kwargs)
    return wrapper_do_twice


def do_twice_and_return_second_time(func):
    def wrapper_do_twice(*args, **kwargs):
        func(*args, **kwargs)
        return func(*args, **kwargs)
    return wrapper_do_twice

