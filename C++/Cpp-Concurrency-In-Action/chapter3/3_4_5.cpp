#include <exception>
#include <memory>

/*
    Code is presenting a thread safe stack that should not allow for race condition.
*/

struct emptyStack : public std::exception
{
    const char *what() const throw();
};

template <typename T>
class ThreadsafeStack
{
public:
    ThreadsafeStack();
    ThreadsafeStack(const ThreadsafeStack &stack);
    // Assignement operator is not allowed for this stack
    ThreadsafeStack &operator=(const ThreadsafeStack &stack) = delete;
};