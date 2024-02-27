#include "RenderCmd.h"

#include <memory>

RenderCmdQueue::RenderCmdQueue()
{
	m_CmdBuffer = new byte[10 * 1024 * 1024]; // 10MB
	m_CmdBufferPtr = m_CmdBuffer; // Set the buffer pointer to the start of the buffer
	memset(m_CmdBuffer, 0, 10 * 1024 * 1024); // 10MB
}

RenderCmdQueue::~RenderCmdQueue()
{
	delete[] m_CmdBuffer;
}

// Allocate memory for a command and return a pointer to it
void* RenderCmdQueue::Allocate(RenderCmdFunc function, uint32_t size)
{
	*reinterpret_cast<RenderCmdFunc*>(m_CmdBufferPtr) = function; // Set the function
	m_CmdBufferPtr += sizeof(RenderCmdFunc); // Move the buffer pointer to the next available space

	*reinterpret_cast<uint32_t*>(m_CmdBufferPtr) = size; // Set the size of the command
	m_CmdBufferPtr += sizeof(uint32_t); // Move the buffer pointer to the next available space

	void* memory = m_CmdBufferPtr; // Set the memory pointer to the next available space
	m_CmdBufferPtr += size; // Move the buffer pointer to the next available space

	m_CmdCount++; // Increment the command count
	return memory; // Return the memory pointer
}

// Execute all commands in the buffer
void RenderCmdQueue::Execute()
{
	byte* buffer = m_CmdBuffer; // Set the buffer pointer to the start of the buffer

	for (uint32_t i = 0; i < m_CmdCount; i++)
	{
		RenderCmdFunc function = *reinterpret_cast<RenderCmdFunc*>(buffer); // Get the function
		buffer += sizeof(RenderCmdFunc); // Move the buffer pointer

		uint32_t size = *reinterpret_cast<uint32_t*>(buffer); // Get the size of the command
		buffer += sizeof(uint32_t); // Move the buffer pointer
		function(buffer); // Call the function with the command data
		buffer += size; // Move the buffer pointer
	}

	m_CmdBufferPtr = m_CmdBuffer; // Set the buffer pointer to the start of the buffer
	m_CmdCount = 0; // Reset the command count
}