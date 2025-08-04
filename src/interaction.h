#ifndef INTERACTION_H
#define INTERACTION_H

#include <vector>
#include <string>

enum class Item
{
  None = -1,
  RawPatty,
  CookedPatty,
  LettuceSlice,
  TomatoSlice,
  Cheese,
  Bun,
  Plate,

  Count,
};

enum class InteractionID
{
  None = -1,
  BigChungus,
};

struct InteractionText
{
  std::string text;
  float textSpeed;
};

class Interaction
{
private:

  double totalTime;
  double nextTimestamp;

  std::vector<InteractionText> text;
  int step;
  bool textFinished;
  bool isFinished;

  InteractionID ID;

public:
  Interaction(InteractionID i);
 
  double getTotalTime();
  double getNextTimestamp();
  void addText(InteractionText t);
  void setID(InteractionID i);
  bool next();
  bool finished();
  std::string getCurrentText();
  void update(double deltaTime);
};

#endif
