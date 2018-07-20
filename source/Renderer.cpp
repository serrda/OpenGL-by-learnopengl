#include "Renderer.h"
#include "VertexArray.h"
#include "ElementBuffer.h"
#include "Shader.h"

void Renderer::Clear() const
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);		// Sets a color to clear screen with. Function is a state-setting function
	glClear(GL_COLOR_BUFFER_BIT);				// Actually clears the screen. Function is a state using function.
}
void Renderer::Draw(const VertexArray & _va, const ElementBuffer & _eb, Shader & _shader) const
{
	_shader.use();//_shader.use();		//binds a shader(program) to be used to render
	_va.Bind();			//binds a vertex array - the array that contains actual data; includes vertex buffer and index buffer; vertex buffer contains vertex data: positions of points to be rendered, teture coordinates, (etc.);
	_eb.Bind();			//index buffer contains: indices into the vertex buffer - so we can know what each element in array is used for
	glDrawElements(GL_TRIANGLES, _eb.GetCount(), GL_UNSIGNED_INT, nullptr);		//says: using index buffer access the vertex buffer and call a shader program on all the vertices individually
}