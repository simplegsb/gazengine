#ifndef MODEL_H_
#define MODEL_H_

class Model
{
	public:
		virtual ~Model()
		{
		}
		
		virtual void draw() = 0;
};

#endif /* MODEL_H_ */
