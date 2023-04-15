#include <stdbool.h>

//　トークンの種類
typedef enum {
  TK_RESERVED, // 記号
  TK_NUM,      // 整数トークン
  TK_EOF,      // 入力の終わりを表すトークン
} TokenKind;

typedef struct Token Token;

// トークン型
struct Token {
  TokenKind kind; // トークンの型
  Token *next;    // 次の入力トークン
  int val;        // kindがTK_NUMの場合、その数値
  char *str;      // トークン文字列
  int len;        // トークンの長さ
};

// 現在着目しているトークン
extern Token *token;

// 入力プログラム
extern char *user_input;

// エラー箇所を報告するための関数
void error_at(char *loc, char *fmt, ...);

// 次のトークンが期待している記号の時には、トークンを１つ読み進めて
// 真を返す。それ以外の場合には偽を返す。
bool consume(char *op);

// 次のトークンが期待している記号の時は、トークンを１つ読み進める。
// それ以外の場合にはエラーを報告する。
void expect(char *op);

// 次のトークンが数値の場合、トークンを１つ読み進めてその数値を返す。
// それ以外の場合はエラーを報告する。
int expect_number();

bool at_eof();

// 新しいトークンを作成してcurに繋げる
Token *new_token(TokenKind kind, Token *cur, char *str, int len);

bool startswitch(char *p, char *q);

Token *tokenize(char *p);

//
// パーサ
//

// 抽象構文木のノードの種類
typedef enum {
  ND_ADD, // +
  ND_SUB, // -
  ND_MUL, // *
  ND_DIV, // /
  ND_EQ,  // ==
  ND_NE,  // !=
  ND_LT,  // <
  ND_LE,  // <=
  ND_NUM, // integer
} NodeKind;

typedef struct Node Node;

// 抽象構文木のノードの型
struct Node {
  NodeKind kind; // ノードの型
  Node *lhs;     // 左辺
  Node *rhs;     // 右辺
  int val;       // kind が ND_NUMの場合のみ使う
};

Node *expr();
Node *equality();
Node *relational();
Node *add();
Node *mul();
Node *unary();
Node *primary();

//
// コード生成
//
void gen(Node *node);
