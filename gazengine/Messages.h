#ifndef MESSAGES_H_
#define MESSAGES_H_

#include <string>

namespace Messages
{
	typedef void(Recipient)(const void*);

	/**
	 * Registers a recipient for the given subject. Standard simplicity events can be found in Events.h.
	 *
	 * @param subject The subject to register the recipient with.
	 * @param recipient The recipient to send messages of the given subject to.
	 */
	void registerRecipient(const std::string& subject, Recipient* recipient);

	/**
	 * Sends the given message to all registered recipients.
	 *
	 * @param subject The subject of the message.
	 * @param message The message to send.
	 */
	void send(const std::string& subject, const void* message);
}

#endif /* MESSAGES_H_ */
