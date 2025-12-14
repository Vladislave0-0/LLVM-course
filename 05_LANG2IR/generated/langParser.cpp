
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
      "program", "funcList", "funcInit", "argList", "statements", "statement", 
      "varInit", "arrInit", "assignment", "ifStatement", "elseStatement", 
      "whileStatement", "call", "callArgList", "returnStatement", "array", 
      "expr"
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
  	4,1,31,181,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,1,0,1,0,1,0,1,1,5,1,39,8,1,10,1,12,1,42,9,1,1,
  	2,1,2,1,2,1,2,3,2,48,8,2,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,3,5,3,58,8,3,10,
  	3,12,3,61,9,3,1,4,5,4,64,8,4,10,4,12,4,67,9,4,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,3,5,78,8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,8,1,8,3,8,98,8,8,1,8,1,8,1,8,1,8,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,3,9,112,8,9,1,10,1,10,1,10,1,10,1,10,1,11,1,11,1,11,1,
  	11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,3,12,130,8,12,1,12,1,12,1,13,1,
  	13,1,13,5,13,137,8,13,10,13,12,13,140,9,13,1,14,1,14,1,14,1,14,1,15,1,
  	15,1,15,1,15,1,15,1,15,1,15,1,15,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,1,16,1,16,3,16,165,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,
  	16,1,16,5,16,176,8,16,10,16,12,16,179,9,16,1,16,0,1,32,17,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,32,0,3,1,0,17,22,1,0,23,25,2,0,16,16,26,
  	26,185,0,34,1,0,0,0,2,40,1,0,0,0,4,43,1,0,0,0,6,54,1,0,0,0,8,65,1,0,0,
  	0,10,77,1,0,0,0,12,79,1,0,0,0,14,85,1,0,0,0,16,97,1,0,0,0,18,103,1,0,
  	0,0,20,113,1,0,0,0,22,118,1,0,0,0,24,126,1,0,0,0,26,133,1,0,0,0,28,141,
  	1,0,0,0,30,145,1,0,0,0,32,164,1,0,0,0,34,35,3,2,1,0,35,36,5,0,0,1,36,
  	1,1,0,0,0,37,39,3,4,2,0,38,37,1,0,0,0,39,42,1,0,0,0,40,38,1,0,0,0,40,
  	41,1,0,0,0,41,3,1,0,0,0,42,40,1,0,0,0,43,44,5,1,0,0,44,45,5,28,0,0,45,
  	47,5,2,0,0,46,48,3,6,3,0,47,46,1,0,0,0,47,48,1,0,0,0,48,49,1,0,0,0,49,
  	50,5,3,0,0,50,51,5,4,0,0,51,52,3,8,4,0,52,53,5,5,0,0,53,5,1,0,0,0,54,
  	59,5,28,0,0,55,56,5,6,0,0,56,58,5,28,0,0,57,55,1,0,0,0,58,61,1,0,0,0,
  	59,57,1,0,0,0,59,60,1,0,0,0,60,7,1,0,0,0,61,59,1,0,0,0,62,64,3,10,5,0,
  	63,62,1,0,0,0,64,67,1,0,0,0,65,63,1,0,0,0,65,66,1,0,0,0,66,9,1,0,0,0,
  	67,65,1,0,0,0,68,78,3,12,6,0,69,78,3,14,7,0,70,78,3,16,8,0,71,78,3,18,
  	9,0,72,78,3,22,11,0,73,74,3,24,12,0,74,75,5,27,0,0,75,78,1,0,0,0,76,78,
  	3,28,14,0,77,68,1,0,0,0,77,69,1,0,0,0,77,70,1,0,0,0,77,71,1,0,0,0,77,
  	72,1,0,0,0,77,73,1,0,0,0,77,76,1,0,0,0,78,11,1,0,0,0,79,80,5,7,0,0,80,
  	81,5,28,0,0,81,82,5,8,0,0,82,83,3,32,16,0,83,84,5,27,0,0,84,13,1,0,0,
  	0,85,86,5,9,0,0,86,87,5,28,0,0,87,88,5,10,0,0,88,89,5,29,0,0,89,90,5,
  	11,0,0,90,91,5,10,0,0,91,92,5,29,0,0,92,93,5,11,0,0,93,94,5,27,0,0,94,
  	15,1,0,0,0,95,98,5,28,0,0,96,98,3,30,15,0,97,95,1,0,0,0,97,96,1,0,0,0,
  	98,99,1,0,0,0,99,100,5,8,0,0,100,101,3,32,16,0,101,102,5,27,0,0,102,17,
  	1,0,0,0,103,104,5,12,0,0,104,105,5,2,0,0,105,106,3,32,16,0,106,107,5,
  	3,0,0,107,108,5,4,0,0,108,109,3,8,4,0,109,111,5,5,0,0,110,112,3,20,10,
  	0,111,110,1,0,0,0,111,112,1,0,0,0,112,19,1,0,0,0,113,114,5,13,0,0,114,
  	115,5,4,0,0,115,116,3,8,4,0,116,117,5,5,0,0,117,21,1,0,0,0,118,119,5,
  	14,0,0,119,120,5,2,0,0,120,121,3,32,16,0,121,122,5,3,0,0,122,123,5,4,
  	0,0,123,124,3,8,4,0,124,125,5,5,0,0,125,23,1,0,0,0,126,127,5,28,0,0,127,
  	129,5,2,0,0,128,130,3,26,13,0,129,128,1,0,0,0,129,130,1,0,0,0,130,131,
  	1,0,0,0,131,132,5,3,0,0,132,25,1,0,0,0,133,138,3,32,16,0,134,135,5,6,
  	0,0,135,137,3,32,16,0,136,134,1,0,0,0,137,140,1,0,0,0,138,136,1,0,0,0,
  	138,139,1,0,0,0,139,27,1,0,0,0,140,138,1,0,0,0,141,142,5,15,0,0,142,143,
  	3,32,16,0,143,144,5,27,0,0,144,29,1,0,0,0,145,146,5,28,0,0,146,147,5,
  	10,0,0,147,148,3,32,16,0,148,149,5,11,0,0,149,150,5,10,0,0,150,151,3,
  	32,16,0,151,152,5,11,0,0,152,31,1,0,0,0,153,154,6,16,-1,0,154,155,5,16,
  	0,0,155,165,3,32,16,9,156,157,5,2,0,0,157,158,3,32,16,0,158,159,5,3,0,
  	0,159,165,1,0,0,0,160,165,3,30,15,0,161,165,5,29,0,0,162,165,5,28,0,0,
  	163,165,3,24,12,0,164,153,1,0,0,0,164,156,1,0,0,0,164,160,1,0,0,0,164,
  	161,1,0,0,0,164,162,1,0,0,0,164,163,1,0,0,0,165,177,1,0,0,0,166,167,10,
  	8,0,0,167,168,7,0,0,0,168,176,3,32,16,9,169,170,10,7,0,0,170,171,7,1,
  	0,0,171,176,3,32,16,8,172,173,10,6,0,0,173,174,7,2,0,0,174,176,3,32,16,
  	7,175,166,1,0,0,0,175,169,1,0,0,0,175,172,1,0,0,0,176,179,1,0,0,0,177,
  	175,1,0,0,0,177,178,1,0,0,0,178,33,1,0,0,0,179,177,1,0,0,0,12,40,47,59,
  	65,77,97,111,129,138,164,175,177
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


//----------------- ProgramContext ------------------------------------------------------------------

langParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::FuncListContext* langParser::ProgramContext::funcList() {
  return getRuleContext<langParser::FuncListContext>(0);
}

tree::TerminalNode* langParser::ProgramContext::EOF() {
  return getToken(langParser::EOF, 0);
}


size_t langParser::ProgramContext::getRuleIndex() const {
  return langParser::RuleProgram;
}


std::any langParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

langParser::ProgramContext* langParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, langParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(34);
    funcList();
    setState(35);
    match(langParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncListContext ------------------------------------------------------------------

langParser::FuncListContext::FuncListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<langParser::FuncInitContext *> langParser::FuncListContext::funcInit() {
  return getRuleContexts<langParser::FuncInitContext>();
}

langParser::FuncInitContext* langParser::FuncListContext::funcInit(size_t i) {
  return getRuleContext<langParser::FuncInitContext>(i);
}


size_t langParser::FuncListContext::getRuleIndex() const {
  return langParser::RuleFuncList;
}


std::any langParser::FuncListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitFuncList(this);
  else
    return visitor->visitChildren(this);
}

langParser::FuncListContext* langParser::funcList() {
  FuncListContext *_localctx = _tracker.createInstance<FuncListContext>(_ctx, getState());
  enterRule(_localctx, 2, langParser::RuleFuncList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(40);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == langParser::T__0) {
      setState(37);
      funcInit();
      setState(42);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FuncInitContext ------------------------------------------------------------------

langParser::FuncInitContext::FuncInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* langParser::FuncInitContext::NAME() {
  return getToken(langParser::NAME, 0);
}

langParser::StatementsContext* langParser::FuncInitContext::statements() {
  return getRuleContext<langParser::StatementsContext>(0);
}

langParser::ArgListContext* langParser::FuncInitContext::argList() {
  return getRuleContext<langParser::ArgListContext>(0);
}


size_t langParser::FuncInitContext::getRuleIndex() const {
  return langParser::RuleFuncInit;
}


std::any langParser::FuncInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitFuncInit(this);
  else
    return visitor->visitChildren(this);
}

langParser::FuncInitContext* langParser::funcInit() {
  FuncInitContext *_localctx = _tracker.createInstance<FuncInitContext>(_ctx, getState());
  enterRule(_localctx, 4, langParser::RuleFuncInit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(43);
    match(langParser::T__0);
    setState(44);
    match(langParser::NAME);
    setState(45);
    match(langParser::T__1);
    setState(47);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == langParser::NAME) {
      setState(46);
      argList();
    }
    setState(49);
    match(langParser::T__2);
    setState(50);
    match(langParser::T__3);
    setState(51);
    statements();
    setState(52);
    match(langParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgListContext ------------------------------------------------------------------

langParser::ArgListContext::ArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> langParser::ArgListContext::NAME() {
  return getTokens(langParser::NAME);
}

tree::TerminalNode* langParser::ArgListContext::NAME(size_t i) {
  return getToken(langParser::NAME, i);
}


size_t langParser::ArgListContext::getRuleIndex() const {
  return langParser::RuleArgList;
}


std::any langParser::ArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitArgList(this);
  else
    return visitor->visitChildren(this);
}

langParser::ArgListContext* langParser::argList() {
  ArgListContext *_localctx = _tracker.createInstance<ArgListContext>(_ctx, getState());
  enterRule(_localctx, 6, langParser::RuleArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(54);
    match(langParser::NAME);
    setState(59);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == langParser::T__5) {
      setState(55);
      match(langParser::T__5);
      setState(56);
      match(langParser::NAME);
      setState(61);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementsContext ------------------------------------------------------------------

langParser::StatementsContext::StatementsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<langParser::StatementContext *> langParser::StatementsContext::statement() {
  return getRuleContexts<langParser::StatementContext>();
}

langParser::StatementContext* langParser::StatementsContext::statement(size_t i) {
  return getRuleContext<langParser::StatementContext>(i);
}


size_t langParser::StatementsContext::getRuleIndex() const {
  return langParser::RuleStatements;
}


std::any langParser::StatementsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitStatements(this);
  else
    return visitor->visitChildren(this);
}

langParser::StatementsContext* langParser::statements() {
  StatementsContext *_localctx = _tracker.createInstance<StatementsContext>(_ctx, getState());
  enterRule(_localctx, 8, langParser::RuleStatements);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 268489344) != 0)) {
      setState(62);
      statement();
      setState(67);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

langParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::VarInitContext* langParser::StatementContext::varInit() {
  return getRuleContext<langParser::VarInitContext>(0);
}

langParser::ArrInitContext* langParser::StatementContext::arrInit() {
  return getRuleContext<langParser::ArrInitContext>(0);
}

langParser::AssignmentContext* langParser::StatementContext::assignment() {
  return getRuleContext<langParser::AssignmentContext>(0);
}

langParser::IfStatementContext* langParser::StatementContext::ifStatement() {
  return getRuleContext<langParser::IfStatementContext>(0);
}

langParser::WhileStatementContext* langParser::StatementContext::whileStatement() {
  return getRuleContext<langParser::WhileStatementContext>(0);
}

langParser::CallContext* langParser::StatementContext::call() {
  return getRuleContext<langParser::CallContext>(0);
}

tree::TerminalNode* langParser::StatementContext::SEMI() {
  return getToken(langParser::SEMI, 0);
}

langParser::ReturnStatementContext* langParser::StatementContext::returnStatement() {
  return getRuleContext<langParser::ReturnStatementContext>(0);
}


size_t langParser::StatementContext::getRuleIndex() const {
  return langParser::RuleStatement;
}


std::any langParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

langParser::StatementContext* langParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 10, langParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(77);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(68);
      varInit();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(69);
      arrInit();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(70);
      assignment();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(71);
      ifStatement();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(72);
      whileStatement();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(73);
      call();
      setState(74);
      match(langParser::SEMI);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(76);
      returnStatement();
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

//----------------- VarInitContext ------------------------------------------------------------------

langParser::VarInitContext::VarInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* langParser::VarInitContext::NAME() {
  return getToken(langParser::NAME, 0);
}

langParser::ExprContext* langParser::VarInitContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

tree::TerminalNode* langParser::VarInitContext::SEMI() {
  return getToken(langParser::SEMI, 0);
}


size_t langParser::VarInitContext::getRuleIndex() const {
  return langParser::RuleVarInit;
}


std::any langParser::VarInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitVarInit(this);
  else
    return visitor->visitChildren(this);
}

langParser::VarInitContext* langParser::varInit() {
  VarInitContext *_localctx = _tracker.createInstance<VarInitContext>(_ctx, getState());
  enterRule(_localctx, 12, langParser::RuleVarInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(79);
    match(langParser::T__6);
    setState(80);
    match(langParser::NAME);
    setState(81);
    match(langParser::T__7);
    setState(82);
    expr(0);
    setState(83);
    match(langParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrInitContext ------------------------------------------------------------------

langParser::ArrInitContext::ArrInitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* langParser::ArrInitContext::NAME() {
  return getToken(langParser::NAME, 0);
}

std::vector<tree::TerminalNode *> langParser::ArrInitContext::INT() {
  return getTokens(langParser::INT);
}

tree::TerminalNode* langParser::ArrInitContext::INT(size_t i) {
  return getToken(langParser::INT, i);
}

tree::TerminalNode* langParser::ArrInitContext::SEMI() {
  return getToken(langParser::SEMI, 0);
}


size_t langParser::ArrInitContext::getRuleIndex() const {
  return langParser::RuleArrInit;
}


std::any langParser::ArrInitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitArrInit(this);
  else
    return visitor->visitChildren(this);
}

langParser::ArrInitContext* langParser::arrInit() {
  ArrInitContext *_localctx = _tracker.createInstance<ArrInitContext>(_ctx, getState());
  enterRule(_localctx, 14, langParser::RuleArrInit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(85);
    match(langParser::T__8);
    setState(86);
    match(langParser::NAME);
    setState(87);
    match(langParser::T__9);
    setState(88);
    match(langParser::INT);
    setState(89);
    match(langParser::T__10);
    setState(90);
    match(langParser::T__9);
    setState(91);
    match(langParser::INT);
    setState(92);
    match(langParser::T__10);
    setState(93);
    match(langParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AssignmentContext ------------------------------------------------------------------

langParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::ExprContext* langParser::AssignmentContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

tree::TerminalNode* langParser::AssignmentContext::SEMI() {
  return getToken(langParser::SEMI, 0);
}

tree::TerminalNode* langParser::AssignmentContext::NAME() {
  return getToken(langParser::NAME, 0);
}

langParser::ArrayContext* langParser::AssignmentContext::array() {
  return getRuleContext<langParser::ArrayContext>(0);
}


size_t langParser::AssignmentContext::getRuleIndex() const {
  return langParser::RuleAssignment;
}


std::any langParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

langParser::AssignmentContext* langParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 16, langParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(97);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(95);
      match(langParser::NAME);
      break;
    }

    case 2: {
      setState(96);
      array();
      break;
    }

    default:
      break;
    }
    setState(99);
    match(langParser::T__7);
    setState(100);
    expr(0);
    setState(101);
    match(langParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IfStatementContext ------------------------------------------------------------------

langParser::IfStatementContext::IfStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::ExprContext* langParser::IfStatementContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

langParser::StatementsContext* langParser::IfStatementContext::statements() {
  return getRuleContext<langParser::StatementsContext>(0);
}

langParser::ElseStatementContext* langParser::IfStatementContext::elseStatement() {
  return getRuleContext<langParser::ElseStatementContext>(0);
}


size_t langParser::IfStatementContext::getRuleIndex() const {
  return langParser::RuleIfStatement;
}


std::any langParser::IfStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitIfStatement(this);
  else
    return visitor->visitChildren(this);
}

langParser::IfStatementContext* langParser::ifStatement() {
  IfStatementContext *_localctx = _tracker.createInstance<IfStatementContext>(_ctx, getState());
  enterRule(_localctx, 18, langParser::RuleIfStatement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(103);
    match(langParser::T__11);
    setState(104);
    match(langParser::T__1);
    setState(105);
    expr(0);
    setState(106);
    match(langParser::T__2);
    setState(107);
    match(langParser::T__3);
    setState(108);
    statements();
    setState(109);
    match(langParser::T__4);
    setState(111);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == langParser::T__12) {
      setState(110);
      elseStatement();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElseStatementContext ------------------------------------------------------------------

langParser::ElseStatementContext::ElseStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::StatementsContext* langParser::ElseStatementContext::statements() {
  return getRuleContext<langParser::StatementsContext>(0);
}


size_t langParser::ElseStatementContext::getRuleIndex() const {
  return langParser::RuleElseStatement;
}


std::any langParser::ElseStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitElseStatement(this);
  else
    return visitor->visitChildren(this);
}

langParser::ElseStatementContext* langParser::elseStatement() {
  ElseStatementContext *_localctx = _tracker.createInstance<ElseStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, langParser::RuleElseStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    match(langParser::T__12);
    setState(114);
    match(langParser::T__3);
    setState(115);
    statements();
    setState(116);
    match(langParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- WhileStatementContext ------------------------------------------------------------------

langParser::WhileStatementContext::WhileStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::ExprContext* langParser::WhileStatementContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

langParser::StatementsContext* langParser::WhileStatementContext::statements() {
  return getRuleContext<langParser::StatementsContext>(0);
}


size_t langParser::WhileStatementContext::getRuleIndex() const {
  return langParser::RuleWhileStatement;
}


std::any langParser::WhileStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitWhileStatement(this);
  else
    return visitor->visitChildren(this);
}

langParser::WhileStatementContext* langParser::whileStatement() {
  WhileStatementContext *_localctx = _tracker.createInstance<WhileStatementContext>(_ctx, getState());
  enterRule(_localctx, 22, langParser::RuleWhileStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(118);
    match(langParser::T__13);
    setState(119);
    match(langParser::T__1);
    setState(120);
    expr(0);
    setState(121);
    match(langParser::T__2);
    setState(122);
    match(langParser::T__3);
    setState(123);
    statements();
    setState(124);
    match(langParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallContext ------------------------------------------------------------------

langParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* langParser::CallContext::NAME() {
  return getToken(langParser::NAME, 0);
}

langParser::CallArgListContext* langParser::CallContext::callArgList() {
  return getRuleContext<langParser::CallArgListContext>(0);
}


size_t langParser::CallContext::getRuleIndex() const {
  return langParser::RuleCall;
}


std::any langParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

langParser::CallContext* langParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 24, langParser::RuleCall);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(126);
    match(langParser::NAME);
    setState(127);
    match(langParser::T__1);
    setState(129);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 805371908) != 0)) {
      setState(128);
      callArgList();
    }
    setState(131);
    match(langParser::T__2);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallArgListContext ------------------------------------------------------------------

langParser::CallArgListContext::CallArgListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<langParser::ExprContext *> langParser::CallArgListContext::expr() {
  return getRuleContexts<langParser::ExprContext>();
}

langParser::ExprContext* langParser::CallArgListContext::expr(size_t i) {
  return getRuleContext<langParser::ExprContext>(i);
}


size_t langParser::CallArgListContext::getRuleIndex() const {
  return langParser::RuleCallArgList;
}


std::any langParser::CallArgListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitCallArgList(this);
  else
    return visitor->visitChildren(this);
}

langParser::CallArgListContext* langParser::callArgList() {
  CallArgListContext *_localctx = _tracker.createInstance<CallArgListContext>(_ctx, getState());
  enterRule(_localctx, 26, langParser::RuleCallArgList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(133);
    expr(0);
    setState(138);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == langParser::T__5) {
      setState(134);
      match(langParser::T__5);
      setState(135);
      expr(0);
      setState(140);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ReturnStatementContext ------------------------------------------------------------------

langParser::ReturnStatementContext::ReturnStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

langParser::ExprContext* langParser::ReturnStatementContext::expr() {
  return getRuleContext<langParser::ExprContext>(0);
}

tree::TerminalNode* langParser::ReturnStatementContext::SEMI() {
  return getToken(langParser::SEMI, 0);
}


size_t langParser::ReturnStatementContext::getRuleIndex() const {
  return langParser::RuleReturnStatement;
}


std::any langParser::ReturnStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitReturnStatement(this);
  else
    return visitor->visitChildren(this);
}

langParser::ReturnStatementContext* langParser::returnStatement() {
  ReturnStatementContext *_localctx = _tracker.createInstance<ReturnStatementContext>(_ctx, getState());
  enterRule(_localctx, 28, langParser::RuleReturnStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(141);
    match(langParser::T__14);
    setState(142);
    expr(0);
    setState(143);
    match(langParser::SEMI);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArrayContext ------------------------------------------------------------------

langParser::ArrayContext::ArrayContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* langParser::ArrayContext::NAME() {
  return getToken(langParser::NAME, 0);
}

std::vector<langParser::ExprContext *> langParser::ArrayContext::expr() {
  return getRuleContexts<langParser::ExprContext>();
}

langParser::ExprContext* langParser::ArrayContext::expr(size_t i) {
  return getRuleContext<langParser::ExprContext>(i);
}


size_t langParser::ArrayContext::getRuleIndex() const {
  return langParser::RuleArray;
}


std::any langParser::ArrayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitArray(this);
  else
    return visitor->visitChildren(this);
}

langParser::ArrayContext* langParser::array() {
  ArrayContext *_localctx = _tracker.createInstance<ArrayContext>(_ctx, getState());
  enterRule(_localctx, 30, langParser::RuleArray);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(145);
    match(langParser::NAME);
    setState(146);
    match(langParser::T__9);
    setState(147);
    expr(0);
    setState(148);
    match(langParser::T__10);
    setState(149);
    match(langParser::T__9);
    setState(150);
    expr(0);
    setState(151);
    match(langParser::T__10);
   
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

std::vector<langParser::ExprContext *> langParser::ExprContext::expr() {
  return getRuleContexts<langParser::ExprContext>();
}

langParser::ExprContext* langParser::ExprContext::expr(size_t i) {
  return getRuleContext<langParser::ExprContext>(i);
}

langParser::ArrayContext* langParser::ExprContext::array() {
  return getRuleContext<langParser::ArrayContext>(0);
}

tree::TerminalNode* langParser::ExprContext::INT() {
  return getToken(langParser::INT, 0);
}

tree::TerminalNode* langParser::ExprContext::NAME() {
  return getToken(langParser::NAME, 0);
}

langParser::CallContext* langParser::ExprContext::call() {
  return getRuleContext<langParser::CallContext>(0);
}


size_t langParser::ExprContext::getRuleIndex() const {
  return langParser::RuleExpr;
}


std::any langParser::ExprContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<langVisitor*>(visitor))
    return parserVisitor->visitExpr(this);
  else
    return visitor->visitChildren(this);
}


langParser::ExprContext* langParser::expr() {
   return expr(0);
}

langParser::ExprContext* langParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  langParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  langParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, langParser::RuleExpr, precedence);

    size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(164);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(154);
      match(langParser::T__15);
      setState(155);
      expr(9);
      break;
    }

    case 2: {
      setState(156);
      match(langParser::T__1);
      setState(157);
      expr(0);
      setState(158);
      match(langParser::T__2);
      break;
    }

    case 3: {
      setState(160);
      array();
      break;
    }

    case 4: {
      setState(161);
      match(langParser::INT);
      break;
    }

    case 5: {
      setState(162);
      match(langParser::NAME);
      break;
    }

    case 6: {
      setState(163);
      call();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(177);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(175);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
        case 1: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(166);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(167);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 8257536) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(168);
          expr(9);
          break;
        }

        case 2: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(169);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(170);
          _la = _input->LA(1);
          if (!((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & 58720256) != 0))) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(171);
          expr(8);
          break;
        }

        case 3: {
          _localctx = _tracker.createInstance<ExprContext>(parentContext, parentState);
          pushNewRecursionContext(_localctx, startState, RuleExpr);
          setState(172);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(173);
          _la = _input->LA(1);
          if (!(_la == langParser::T__15

          || _la == langParser::T__25)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(174);
          expr(7);
          break;
        }

        default:
          break;
        } 
      }
      setState(179);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool langParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 16: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool langParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 8);
    case 1: return precpred(_ctx, 7);
    case 2: return precpred(_ctx, 6);

  default:
    break;
  }
  return true;
}

void langParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  langParserInitialize();
#else
  ::antlr4::internal::call_once(langParserOnceFlag, langParserInitialize);
#endif
}
