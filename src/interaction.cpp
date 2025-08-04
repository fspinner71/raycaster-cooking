#include "interaction.h"

Interaction::Interaction(InteractionID i)
{
  step = 0;
  textFinished = false;
  totalTime = 0;
  nextTimestamp = 0;
  isFinished = false;
  setID(i);
}
double Interaction::getTotalTime()
{
  return totalTime;
}

double Interaction::getNextTimestamp()
{
  return nextTimestamp;
}

void Interaction::addText(InteractionText t)
{
  text.push_back(t);
}

bool Interaction::finished()
{
  return isFinished;
}

void Interaction::setID(InteractionID i)
{
  ID = i;
  switch(ID)
  {
  case InteractionID::BigChungus:
      addText({"HELLO", 20});
      addText({"This is the stove", 5});
    break;
  default:
    break;
  }
}

bool Interaction::next()
{
  if(!textFinished)
  {
    textFinished = true;
    return false;
  }


  if(step + 1 >= text.size())
  {
    isFinished = true;
  } else {
    step++;
    nextTimestamp = totalTime;
    textFinished = false;
  }

  return true;
}

std::string Interaction::getCurrentText()
{
  if(text.size() <= 0)
  {
    return "";
  }
  InteractionText currentText = text.at(step);
  int numChars = textFinished ? currentText.text.length() : (int)(currentText.textSpeed * (totalTime - nextTimestamp));
  if(numChars > currentText.text.length())
  {
    numChars = currentText.text.length();
  }
  return text.at(step).text.substr(0, numChars);
}
void Interaction::update(double deltaTime)
{
  if(text.size() <= 0)
  {
    isFinished = true;
    return;
  }
  totalTime += deltaTime;
  InteractionText currentText = text.at(step);
  if(currentText.textSpeed * (totalTime - nextTimestamp) > currentText.text.length())
  {
    textFinished = true;
  }
}
