// Helper functions
//  Idealy this would be done using pixels from an image, but for the sake of time it is hard coded
struct vectorQueue *loadPoints(void) {
  struct vectorQueue *q = NULL;
  struct vector p1 = (struct vector){ width / 2 - 6, height / 2 };
  struct vector p2 = (struct vector){ width / 2 - 6, height / 2 + 6 };
  struct vector p3 = (struct vector){ width / 2 + 6, height / 2 + 6 };
  struct vector p4 = (struct vector){ width / 2 + 6, height / 2 - 6 };
  struct vector p5 = (struct vector){ width / 2 - 6, height / 2 - 6 };
  struct vector p6 = (struct vector){ width / 2 - 6, height / 2 };
  struct vector p7 = (struct vector){ width / 2, height / 2 };
  struct vector p8 = (struct vector){ 0, 3 };

  q = vectorQueueInit();
  vectorQueueEnqueue(q, p1);
  vectorQueueEnqueue(q, p2);
  vectorQueueEnqueue(q, p3);
  vectorQueueEnqueue(q, p4);
  vectorQueueEnqueue(q, p5);
  vectorQueueEnqueue(q, p6);
  vectorQueueEnqueue(q, p7);
//  vectorQueueEnqueue(q, p8);
  return (q);
}

// Vector math
float distanceBetweenVectors(struct vector p1, struct vector p2, float xOffset, float yOffset)
{
  float distance = sqrt(pow(p2.x + xOffset - p1.x, 2) + pow(p2.y + yOffset - p1.y, 2));

  return (distance);
}

// Vector Queue
struct vectorQueue *vectorQueueInit(void) {
  struct vectorQueue *q = NULL;
  if (!(q = (struct vectorQueue *)malloc(sizeof(struct vectorQueue))))
    exit(1);
  q->first = NULL;
  q->last = NULL;
  return (q);
}

void vectorQueueEnqueue(struct vectorQueue *q, struct vector point) {
  struct vectorNode *addition = NULL;

  if (q != NULL && (addition = (struct vectorNode *)malloc(sizeof(struct vectorNode))))
  {
    addition->point = point;
    addition->next = NULL;
    if (q->first == NULL)
      q->first = addition;
    if (q->last != NULL)
      q->last->next = addition;
    q->last = addition;
  }
}

struct vector vectorQueueDequeue(struct vectorQueue *q) {
  struct vectorNode *temp = NULL;
  struct vector toReturn = (struct vector) { -1, -1 };

  if (q != NULL && q->first != NULL) {
    toReturn = q->first->point;
    temp = q->first->next;
    free(q->first);
    q->first = temp;
  }
  return (toReturn);
}

bool isVectorQueueEmpty(struct vectorQueue *q)
{
  return (q->first == NULL);
}
