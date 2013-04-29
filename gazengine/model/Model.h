#ifndef MODEL_H_
#define MODEL_H_

class Model
{
	public:
		enum PrimitiveType
		{
			LINE_LIST,

			NA,

			TRIANGLE_LIST
		};

		virtual ~Model()
		{
		}
		
		virtual void draw() = 0;
		
		virtual PrimitiveType getPrimitiveType() const = 0;
};

#endif /* MODEL_H_ */
