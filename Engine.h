#ifndef ENGINE_H_
#define ENGINE_H_

class Engine
{
	public:
		virtual ~Engine()
		{
		}

		virtual void advance() = 0;

		virtual void destroy() = 0;

		virtual void init() = 0;
};

#endif /* ENGINE_H_ */
