
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
      "NUM", "PLUS", "WS"
    },
    std::vector<std::string>{
      "DEFAULT_TOKEN_CHANNEL", "HIDDEN"
    },
    std::vector<std::string>{
      "DEFAULT_MODE"
    },
    std::vector<std::string>{
      "", "", "'+'"
    },
    std::vector<std::string>{
      "", "NUM", "PLUS", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,0,3,21,6,-1,2,0,7,0,2,1,7,1,2,2,7,2,1,0,4,0,9,8,0,11,0,12,0,10,1,1,
  	1,1,1,2,4,2,16,8,2,11,2,12,2,17,1,2,1,2,0,0,3,1,1,3,2,5,3,1,0,2,1,0,48,
  	57,3,0,9,10,13,13,32,32,22,0,1,1,0,0,0,0,3,1,0,0,0,0,5,1,0,0,0,1,8,1,
  	0,0,0,3,12,1,0,0,0,5,15,1,0,0,0,7,9,7,0,0,0,8,7,1,0,0,0,9,10,1,0,0,0,
  	10,8,1,0,0,0,10,11,1,0,0,0,11,2,1,0,0,0,12,13,5,43,0,0,13,4,1,0,0,0,14,
  	16,7,1,0,0,15,14,1,0,0,0,16,17,1,0,0,0,17,15,1,0,0,0,17,18,1,0,0,0,18,
  	19,1,0,0,0,19,20,6,2,0,0,20,6,1,0,0,0,3,0,10,17,1,6,0,0
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
