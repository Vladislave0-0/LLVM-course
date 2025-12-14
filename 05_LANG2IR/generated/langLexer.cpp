
// Generated from lang.g4 by ANTLR 4.13.1


#include "langLexer.h"


using namespace antlr4;



using namespace antlr4;

namespace {

struct LangLexerStaticData final {
  LangLexerStaticData(std::vector<std::string> ruleNames,
                          std::vector<std::string> channelNames,
                          std::vector<std::string> modeNames,
                          std::vector<std::string> literalNames,
                          std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), channelNames(std::move(channelNames)),
        modeNames(std::move(modeNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LangLexerStaticData(const LangLexerStaticData&) = delete;
  LangLexerStaticData(LangLexerStaticData&&) = delete;
  LangLexerStaticData& operator=(const LangLexerStaticData&) = delete;
  LangLexerStaticData& operator=(LangLexerStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> channelNames;
  const std::vector<std::string> modeNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag langlexerLexerOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
LangLexerStaticData *langlexerLexerStaticData = nullptr;

void langlexerLexerInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (langlexerLexerStaticData != nullptr) {
    return;
  }
#else
  assert(langlexerLexerStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LangLexerStaticData>(
    std::vector<std::string>{
      "T__0", "T__1", "T__2", "T__3", "T__4", "T__5", "T__6", "T__7", "T__8", 
      "T__9", "T__10", "T__11", "T__12", "T__13", "T__14", "T__15", "T__16", 
      "T__17", "T__18", "T__19", "T__20", "T__21", "T__22", "T__23", "T__24", 
      "T__25", "SEMI", "NAME", "INT", "WS", "COMMENT"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "'func'", "'('", "')'", "'{'", "'}'", "','", "'var'", "'='", "'array'", 
      "'['", "']'", "'if'", "'else'", "'while'", "'return'", "'-'", "'=='", 
      "'!='", "'>'", "'>='", "'<'", "'<='", "'*'", "'/'", "'%'", "'+'", 
      "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "SEMI", "NAME", "INT", "WS", 
      "COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,31,173,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,
  	6,2,7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,
  	7,14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,2,21,
  	7,21,2,22,7,22,2,23,7,23,2,24,7,24,2,25,7,25,2,26,7,26,2,27,7,27,2,28,
  	7,28,2,29,7,29,2,30,7,30,1,0,1,0,1,0,1,0,1,0,1,1,1,1,1,2,1,2,1,3,1,3,
  	1,4,1,4,1,5,1,5,1,6,1,6,1,6,1,6,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,9,1,
  	9,1,10,1,10,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,13,1,13,1,13,1,
  	13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,15,1,15,1,16,1,16,1,
  	16,1,17,1,17,1,17,1,18,1,18,1,19,1,19,1,19,1,20,1,20,1,21,1,21,1,21,1,
  	22,1,22,1,23,1,23,1,24,1,24,1,25,1,25,1,26,1,26,1,27,1,27,5,27,146,8,
  	27,10,27,12,27,149,9,27,1,28,4,28,152,8,28,11,28,12,28,153,1,29,4,29,
  	157,8,29,11,29,12,29,158,1,29,1,29,1,30,1,30,1,30,1,30,5,30,167,8,30,
  	10,30,12,30,170,9,30,1,30,1,30,0,0,31,1,1,3,2,5,3,7,4,9,5,11,6,13,7,15,
  	8,17,9,19,10,21,11,23,12,25,13,27,14,29,15,31,16,33,17,35,18,37,19,39,
  	20,41,21,43,22,45,23,47,24,49,25,51,26,53,27,55,28,57,29,59,30,61,31,
  	1,0,5,2,0,65,90,97,122,4,0,48,57,65,90,95,95,97,122,1,0,48,57,3,0,9,10,
  	13,13,32,32,2,0,10,10,13,13,176,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,0,
  	7,1,0,0,0,0,9,1,0,0,0,0,11,1,0,0,0,0,13,1,0,0,0,0,15,1,0,0,0,0,17,1,0,
  	0,0,0,19,1,0,0,0,0,21,1,0,0,0,0,23,1,0,0,0,0,25,1,0,0,0,0,27,1,0,0,0,
  	0,29,1,0,0,0,0,31,1,0,0,0,0,33,1,0,0,0,0,35,1,0,0,0,0,37,1,0,0,0,0,39,
  	1,0,0,0,0,41,1,0,0,0,0,43,1,0,0,0,0,45,1,0,0,0,0,47,1,0,0,0,0,49,1,0,
  	0,0,0,51,1,0,0,0,0,53,1,0,0,0,0,55,1,0,0,0,0,57,1,0,0,0,0,59,1,0,0,0,
  	0,61,1,0,0,0,1,63,1,0,0,0,3,68,1,0,0,0,5,70,1,0,0,0,7,72,1,0,0,0,9,74,
  	1,0,0,0,11,76,1,0,0,0,13,78,1,0,0,0,15,82,1,0,0,0,17,84,1,0,0,0,19,90,
  	1,0,0,0,21,92,1,0,0,0,23,94,1,0,0,0,25,97,1,0,0,0,27,102,1,0,0,0,29,108,
  	1,0,0,0,31,115,1,0,0,0,33,117,1,0,0,0,35,120,1,0,0,0,37,123,1,0,0,0,39,
  	125,1,0,0,0,41,128,1,0,0,0,43,130,1,0,0,0,45,133,1,0,0,0,47,135,1,0,0,
  	0,49,137,1,0,0,0,51,139,1,0,0,0,53,141,1,0,0,0,55,143,1,0,0,0,57,151,
  	1,0,0,0,59,156,1,0,0,0,61,162,1,0,0,0,63,64,5,102,0,0,64,65,5,117,0,0,
  	65,66,5,110,0,0,66,67,5,99,0,0,67,2,1,0,0,0,68,69,5,40,0,0,69,4,1,0,0,
  	0,70,71,5,41,0,0,71,6,1,0,0,0,72,73,5,123,0,0,73,8,1,0,0,0,74,75,5,125,
  	0,0,75,10,1,0,0,0,76,77,5,44,0,0,77,12,1,0,0,0,78,79,5,118,0,0,79,80,
  	5,97,0,0,80,81,5,114,0,0,81,14,1,0,0,0,82,83,5,61,0,0,83,16,1,0,0,0,84,
  	85,5,97,0,0,85,86,5,114,0,0,86,87,5,114,0,0,87,88,5,97,0,0,88,89,5,121,
  	0,0,89,18,1,0,0,0,90,91,5,91,0,0,91,20,1,0,0,0,92,93,5,93,0,0,93,22,1,
  	0,0,0,94,95,5,105,0,0,95,96,5,102,0,0,96,24,1,0,0,0,97,98,5,101,0,0,98,
  	99,5,108,0,0,99,100,5,115,0,0,100,101,5,101,0,0,101,26,1,0,0,0,102,103,
  	5,119,0,0,103,104,5,104,0,0,104,105,5,105,0,0,105,106,5,108,0,0,106,107,
  	5,101,0,0,107,28,1,0,0,0,108,109,5,114,0,0,109,110,5,101,0,0,110,111,
  	5,116,0,0,111,112,5,117,0,0,112,113,5,114,0,0,113,114,5,110,0,0,114,30,
  	1,0,0,0,115,116,5,45,0,0,116,32,1,0,0,0,117,118,5,61,0,0,118,119,5,61,
  	0,0,119,34,1,0,0,0,120,121,5,33,0,0,121,122,5,61,0,0,122,36,1,0,0,0,123,
  	124,5,62,0,0,124,38,1,0,0,0,125,126,5,62,0,0,126,127,5,61,0,0,127,40,
  	1,0,0,0,128,129,5,60,0,0,129,42,1,0,0,0,130,131,5,60,0,0,131,132,5,61,
  	0,0,132,44,1,0,0,0,133,134,5,42,0,0,134,46,1,0,0,0,135,136,5,47,0,0,136,
  	48,1,0,0,0,137,138,5,37,0,0,138,50,1,0,0,0,139,140,5,43,0,0,140,52,1,
  	0,0,0,141,142,5,59,0,0,142,54,1,0,0,0,143,147,7,0,0,0,144,146,7,1,0,0,
  	145,144,1,0,0,0,146,149,1,0,0,0,147,145,1,0,0,0,147,148,1,0,0,0,148,56,
  	1,0,0,0,149,147,1,0,0,0,150,152,7,2,0,0,151,150,1,0,0,0,152,153,1,0,0,
  	0,153,151,1,0,0,0,153,154,1,0,0,0,154,58,1,0,0,0,155,157,7,3,0,0,156,
  	155,1,0,0,0,157,158,1,0,0,0,158,156,1,0,0,0,158,159,1,0,0,0,159,160,1,
  	0,0,0,160,161,6,29,0,0,161,60,1,0,0,0,162,163,5,47,0,0,163,164,5,47,0,
  	0,164,168,1,0,0,0,165,167,8,4,0,0,166,165,1,0,0,0,167,170,1,0,0,0,168,
  	166,1,0,0,0,168,169,1,0,0,0,169,171,1,0,0,0,170,168,1,0,0,0,171,172,6,
  	30,0,0,172,62,1,0,0,0,5,0,147,153,158,168,1,6,0,0
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  langlexerLexerStaticData = staticData.release();
}

}

langLexer::langLexer(CharStream *input) : Lexer(input) {
  langLexer::initialize();
  _interpreter = new atn::LexerATNSimulator(this, *langlexerLexerStaticData->atn, langlexerLexerStaticData->decisionToDFA, langlexerLexerStaticData->sharedContextCache);
}

langLexer::~langLexer() {
  delete _interpreter;
}

std::string langLexer::getGrammarFileName() const {
  return "lang.g4";
}

const std::vector<std::string>& langLexer::getRuleNames() const {
  return langlexerLexerStaticData->ruleNames;
}

const std::vector<std::string>& langLexer::getChannelNames() const {
  return langlexerLexerStaticData->channelNames;
}

const std::vector<std::string>& langLexer::getModeNames() const {
  return langlexerLexerStaticData->modeNames;
}

const dfa::Vocabulary& langLexer::getVocabulary() const {
  return langlexerLexerStaticData->vocabulary;
}

antlr4::atn::SerializedATNView langLexer::getSerializedATN() const {
  return langlexerLexerStaticData->serializedATN;
}

const atn::ATN& langLexer::getATN() const {
  return *langlexerLexerStaticData->atn;
}




void langLexer::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  langlexerLexerInitialize();
#else
  ::antlr4::internal::call_once(langlexerLexerOnceFlag, langlexerLexerInitialize);
#endif
}
