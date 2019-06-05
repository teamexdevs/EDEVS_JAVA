#ifndef __ENTSTR_HPP__
#define __ENTSTR_HPP__

#include "Digraph.hpp"
#include "List.hpp"

class EntStr : public Digraph {
public:
   Model *CurrentItem;
   double Clock, LimitClock, CClock;
   List   ChildList;

public:
   EntStr(std::string);

   void SetLimit(double);
   int  SetCurrentItem(Model *);
   int  SCI(Model *);
   int  SetCurrentItem(std::string);
   int  AddItem(Model *);
   int  AddCouple(Model *, Model *, std::string, std::string);
   int  AddCouple(std::string, std::string, std::string, std::string);

   double SetClock(double );
   double GetClock(void);
   double AddClock(double );

   void Initialize(void);
   void Restart(void);
   void StepStart(void);
   void OutputFN(double);

   void IntTransition(double );
   void Inject(std::string, std::string);

   void Done(Model *, double);
   void DoneInit(Model *, double);

   void IntTransition(void);
   void Output(double);
   void Output(void);
   void InitialModel(void);
};

#endif   // __ENTSTR_HPP__