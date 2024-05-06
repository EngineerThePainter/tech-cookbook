#include <exception>
#include <memory>
#include <mutex>
#include <stack>

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
    ThreadsafeStack() {}
    ThreadsafeStack(const ThreadsafeStack &stack)
    {
        std::lock_guard<std::mutex> lock(stack.m_);
        data = stack.data_;
    }
    // Assignement operator is not allowed for this stack
    ThreadsafeStack &operator=(const ThreadsafeStack &stack) = delete;

    void push(T new_value)
    {
        std::lock_guard<std::mutex> lock(m_);
        data.push(std::move(new_value));
    }

    std::shared_ptr<T> pop()
    {
        std::lock_guard<std::mutex> lock(m_);
        if (data_.empty())
        {
            throw emptyStack();
        }
        std::shared_ptr<T> const res(std::make_shared<T>(data_.top()));
        data_.pop();
        return res;
    }

    void pop(T &value)
    {
        std::lock_guard<std::mutex> lock(m_);
        if (data_.empty())
        {
            throw emptyStack();
        }
        value = data_.top();
        data_.pop();
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lock(m_);
        return data_.empty();
    }

private:
    std::stack<T> data_;
    mutable std::mutex m_;
};

int main()
{

    return 0;
}