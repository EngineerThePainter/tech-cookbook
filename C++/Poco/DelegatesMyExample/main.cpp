#include <iostream>
#include <string>

#include <Poco/BasicEvent.h>
#include <Poco/Delegate.h>

class NormalStudent {
  public:
  void doPushUps(int n) {
    std::cout << "Normal  Student: I have to do: " << n << " push-ups." << std::endl;
  }
};

class NormalTrainer {
  public:
  void sayNumberOfReps(NormalStudent& student) {
    student.doPushUps(push_ups_nb_);
  }
  private:
  const int push_ups_nb_ = 42;
};

class EventTrainer
{
public:
  Poco::BasicEvent<int> reps_event_;
  void sayNumberOfReps(int n) { reps_event_(this, n); }
};

class EventStudent
{
public:
  void onNumberOfReps(const void* sender, int& arg)
  {
    std::cout << "I have to do: " << arg << " push-ups." << std::endl;
  }
};

int main()
{
  NormalTrainer normal_trainer_;
  NormalStudent normal_student_;
  normal_trainer_.sayNumberOfReps(normal_student_);

  EventTrainer trainer;
  EventStudent student;

  trainer.reps_event_ += Poco::delegate(&student, &EventStudent::onNumberOfReps);
  trainer.sayNumberOfReps(42);
  trainer.reps_event_ -= Poco::delegate(&student, &EventStudent::onNumberOfReps);

  return 0;
}