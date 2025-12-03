
// Generated from lang.g4 by ANTLR 4.13.1


#include "langVisitor.h"

#include "langParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct LangParserStaticData final {
  LangParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  LangParserStaticData(const LangParserStaticData&) = delete;
  LangParserStaticData(LangParserStaticData&&) = delete;
  LangParserStaticData& operator=(const LangParserStaticData&) = delete;
  LangParserStaticData& operator=(LangParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag langParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
LangParserStaticData *langParserStaticData = nullptr;

void langParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (langParserStaticData != nullptr) {
    return;
  }
#else
  assert(langParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<LangParserStaticData>(
    std::vector<std::string>{
      "prog", "expr"
    },
    std::vector<std::string>{
      "", "", "'+'"
    },
    std::vector<std::string>{
      "", "NUM", "PLUS", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,3,14,2,0,7,0,2,1,7,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,3,1,12,8,1,1,1,0,
  	0,2,0,2,0,0,12,0,4,1,0,0,0,2,11,1,0,0,0,4,5,3,2,1,0,5,6,5,0,0,1,6,1,1,
  	0,0,0,7,8,5,1,0,0,8,9,5,2,0,0,9,12,5,1,0,0,10,12,5,1,0,0,11,7,1,0,0,0,
  	11,10,1,0,0,0,12,3,1,0,0,0,1,11
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  langParserStaticData = staticData.release();
}

}

langParser::langParser(TokenStream *input) : langParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

langParser::langParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  langParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *langParserStaticData->atn, langParserStaticData->decisionToDFA, langParserStaticData->sharedContextCache, options);
}

langParser::~langParser() {
  delete _interpreter;
}

const atn::ATN& langParser::getATN() const {
  return *langParserStaticData->atn;
}

std::string langParser::getGrammarFileName() const {
  return "lang.g4";
}

const std::vector<std::string>& langParser::getRuleNames() const {
  return langParserStaticData->ruleNames;
}

const dfa::Vocabulary& langParser::getVocabulary() const {
  return langParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView langParser::getSerializedATN() const {
  return langParserStaticData->serializedATN;
}


//----------------- ProgContext ------------------------------------------------------------------

langParser::ProgContext::ProgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::ExprContext* langParser::ProgContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

tree::TerminalNode* langParser::ProgContext::EOF() {
  return getToken(langParser::EOF, 0);
}


size_t langParser::ProgContext::getRuleIndex() const {
  return langParser::RuleProg;
}


std::any langParser::ProgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitProg(this);
  else
    return visitor->visitChildren(this);
}

langParser::ProgContext* langParser::prog() {
  ProgContext *_localctx = _tracker.createInstance<ProgContext>(_ctx, getState());
  enterRule(_localctx, 0, langParser::RuleProg);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(4);
    expr();
    setState(5);
    match(langParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

langParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t langParser::ExprContext::getRuleIndex() const {
  return langParser::RuleExpr;
}

void langParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AddContext ------------------------------------------------------------------

tree::TerminalNode* langParser::AddContext::PLUS() {
  return getToken(langParser::PLUS, 0);
}

std::vector<tree::TerminalNode *> langParser::AddContext::NUM() {
  return getTokens(langParser::NUM);
}

tree::TerminalNode* langParser::AddContext::NUM(size_t i) {
  return getToken(langParser::NUM, i);
}

langParser::AddContext::AddContext(ExprContext *ctx) { copyFrom(ctx); }


std::any langParser::AddContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitAdd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleNumContext ------------------------------------------------------------------

tree::TerminalNode* langParser::SingleNumContext::NUM() {
  return getToken(langParser::NUM, 0);
}

langParser::SingleNumContext::SingleNumContext(ExprContext *ctx) { copyFrom(ctx); }


std::any langParser::SingleNumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitSingleNum(this);
  else
    return visitor->visitChildren(this);
}
langParser::ExprContext* langParser::expr() {
  ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, getState());
  enterRule(_localctx, 2, langParser::RuleExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(11);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<langParser::AddContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(7);
      antlrcpp::downCast<AddContext *>(_localctx)->left = match(langParser::NUM);
      setState(8);
      match(langParser::PLUS);
      setState(9);
      antlrcpp::downCast<AddContext *>(_localctx)->right = match(langParser::NUM);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<langParser::SingleNumContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(10);
      match(langParser::NUM);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

void langParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  langParserInitialize();
#else
  ::antlr4::internal::call_once(langParserOnceFlag, langParserInitialize);
#endif
}
