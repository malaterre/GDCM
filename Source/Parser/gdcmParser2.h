class Tag
{
  uint16_t Group;
  uint16_t Element;
};

class ValueRequest
{
  std::vector<Tag> RequestedTags;
  std::vector<char*> ValueFound; // Potentially found...
};

class Parser
{
  // Find out if the file is
  // Big/LittleEndian
  // DICOMV3/ACRNEMA/Papyrus
  void Initialize();

  void SetValueRequest(ValueRequest &request);
  void ReadElements();

private:
  int Type; //ACRNEMA/DICOMV3,Papyrus
  int SwapType; //Big/Bad/LittleEndian
};

class Seeker : public Parser
{
  // If no group lenght (or wrong) compute them in internal
  // array
  void ComputeGroupLength();

  bool FindElement(const Tag &tag);
  void ReadElement(const Tag &tag, char *value);

private:
  std::vector< std::pair<group_number, group_length> > GroupLengths;
};
