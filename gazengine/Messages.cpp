#include <map>
#include <vector>

#include "Messages.h"

using namespace std;

namespace Messages
{
	map<const string, vector<Recipient*> > recipients;

	void registerRecipient(const string& subject, Recipient* recipient)
	{
		if (recipients.find(subject) == recipients.end())
		{
			recipients.insert(
				pair<const string, vector<Recipient*> >(subject, vector<Recipient*>()));
		}

		recipients.find(subject)->second.push_back(recipient);
	}

	void send(const string& subject, const void* message)
	{
		if (recipients.find(subject) == recipients.end())
		{
			return;
		}

		vector<Recipient*>& registeredRecipients = recipients.find(subject)->second;

		// Does not use C++11 for loop as elements could be added to the vector while iterating.
		// Take care - this is a fragile 'solution'.
		for (unsigned int index = 0; index < registeredRecipients.size(); index++)
		{
			registeredRecipients.at(index)(message);
		}
	}
}
