/* Functions implemented in drawplant.h */
#include <glm/glm.hpp>
void beginPlant(void);
void drawPlant(int level, glm::mat3 t);
int init_resources(void);
void free_resources(void);
void drawLeaf(glm::mat3 t);
glm::mat3 turnLeft(glm::mat3 t, float angle);
glm::mat3 turnRight(glm::mat3 t, float angle);
glm::mat3 drawStem(int level, glm::mat3 m);
glm::mat3 drawLine(glm::mat3 m);
float curveValue(float t, float a, float b, float c);
void getCurve(float x[], float y[]);
void getCurve2(float x[], float y[]);
void drawPalm(glm::mat3 t);
glm::mat3 drawPalmStem(glm::mat3 m);
glm::mat3 forward(glm::mat3 t, float x, float y);
