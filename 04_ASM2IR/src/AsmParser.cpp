#include "../include/AsmParser.hpp"
#include <cctype>
#include <fstream>
#include <sstream>

namespace asm2ir {

bool AsmParser::parse() {
  std::ifstream file(filename);
  if (!file.is_open())
    return false;

  std::string line;
  size_t line_number = 0;

  while (std::getline(file, line)) {
    ++line_number;
    processLine(line, line_number);
  }

  return true;
}

void AsmParser::processLine(const std::string &input_line, size_t line_number) {
  // Убираем комментарии.
  std::string line = input_line;
  size_t comment_pos = line.find(';');
  if (comment_pos != std::string::npos) {
    line = line.substr(0, comment_pos);
  }

  // Убираем пробелы с обеих сторон.
  line.erase(0, line.find_first_not_of(" \t"));
  line.erase(line.find_last_not_of(" \t") + 1);

  if (line.empty())
    return;

  // Проверка, является ли строка меткой. Сохраняем её.
  if (line.back() == ':') {
    std::string label = line.substr(0, line.size() - 1);
    labels[label] = instructions.size();
    return;
  }

  // Разделяем строку на токены.
  std::vector<std::string> tokens;
  tokenizeLine(line, tokens);

  // Если токенов на строке не было.
  if (tokens.empty())
    return;

  // Сохраняем инструкцию.
  Instruction instr;
  instr.opcode = tokens[0];
  instr.line_number = line_number;

  // Обработать операнды
  for (size_t i = 1; i < tokens.size(); ++i) {
    std::string token = tokens[i];

    Operand operand;

    // Проверить тип операнда
    if (token[0] == 'x' && std::isdigit(token[1])) {
      operand.type = OperandType::REGISTER;
      operand.value = token.substr(1);
    } else if (token[0] == '%') {
      operand.type = OperandType::REGISTER;
      operand.value = token.substr(1);
    } else if (std::isdigit(token[0]) || token[0] == '-') {
      operand.type = OperandType::IMMEDIATE;
      operand.value = token;
    } else if (std::isalpha(token[0])) {
      operand.type = OperandType::LABEL;
      operand.value = token;
    } else {
      operand.type = OperandType::MEMORY;
      operand.value = token;
    }

    instr.operands.push_back(operand);
  }

  instructions.push_back(instr);
}

void AsmParser::tokenizeLine(const std::string &line,
                             std::vector<std::string> &tokens) {
  std::istringstream iss(line);
  std::string token;

  while (iss >> token) {
    // Разделяем операнды через запятые.
    size_t pos = 0;
    size_t comma_pos = token.find(',');

    while (comma_pos != std::string::npos) {
      if (comma_pos > pos)
        tokens.push_back(token.substr(pos, comma_pos - pos));

      pos = comma_pos + 1;
      comma_pos = token.find(',', pos);
    }

    if (pos < token.size())
      tokens.push_back(token.substr(pos));
  }
}

const std::vector<Instruction> &AsmParser::getInstructions() const {
  return instructions;
}

const std::unordered_map<std::string, size_t> &AsmParser::getLabels() const {
  return labels;
}

} // namespace asm2ir
