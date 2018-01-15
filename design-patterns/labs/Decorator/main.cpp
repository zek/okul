// Please implement missing classes so that it is possible to
// represent a person with various properties.

// Please, note that there is PersonI which is an interface defining
// purely virtual method IntroduceYourself and there is a class called
// Person, which represents a person only with name.

#include<iostream>
#include"Persons.h"

int main ()
{
  PersonI* simple = new Person ("Rick Sanchez");
  simple->IntroduceYourself();

  std::cout<<std::endl;

  PersonI* old = new Age (1032, new Person ("Fry"));
  old->IntroduceYourself();

  std::cout<<std::endl;

  PersonI* youngKiller = new Profession ("killer", new Age(14, new Person ("Mathilda")));
  youngKiller->IntroduceYourself();

  std::cout<<std::endl;

  PersonI* skilledGravedigger = new Profession("gravedigger", new Skill("run fast", new Person ("Gary")));
  skilledGravedigger->IntroduceYourself();

  std::cout<<std::endl;

  PersonI* skilledPerson = new Skill("stand", new Person ("Henry Poll"));
  skilledPerson->IntroduceYourself();

  std::cout<<std::endl;

  PersonI* skilledOldVagabond = new Profession("vagabond", new Skill("wander", new Age(45, new Person ("Lucky Luke"))));
  skilledOldVagabond->IntroduceYourself();


  return 0;
}
/*
My name is: Rick Sanchez

My name is: Fry
I am 1032 years old.

My name is: Mathilda
I am 14 years old.
I work as a killer.

My name is: Gary
I can run fast.
I work as a gravedigger.

My name is: Henry Poll
I can stand.

My name is: Lucky Luke
I am 45 years old.
I can wander.
I work as a vagabond.
*/