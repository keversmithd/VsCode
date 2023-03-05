#ifndef NMLRENDAGEN
#define NMLRENDAGEN

struct NMLRenderingAgent
{
private:
	bool TransformFeedback;
public:
	NMLRenderingAgent();
	int DrawElements();
	int DrawArrays();

	~NMLRenderingAgent();
};

#endif
