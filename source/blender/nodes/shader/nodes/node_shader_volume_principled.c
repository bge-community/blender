/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * The Original Code is Copyright (C) 2005 Blender Foundation.
 * All rights reserved.
 */

#include "../node_shader_util.h"

/* **************** OUTPUT ******************** */

static bNodeSocketTemplate sh_node_volume_principled_in[] = {
	{	SOCK_RGBA, 1, N_("Color"),					0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f},
	{	SOCK_STRING, 1, N_("Color Attribute"),		0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{	SOCK_FLOAT, 1, N_("Density"),				1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1000.0f},
	{	SOCK_STRING, 1, N_("Density Attribute"),	1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{	SOCK_FLOAT, 1, N_("Anisotropy"),			0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, PROP_FACTOR},
	{	SOCK_RGBA, 1, N_("Absorption Color"),		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f},
	{	SOCK_FLOAT, 1, N_("Emission Strength"),		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1000.0f},
	{	SOCK_RGBA, 1, N_("Emission Color"),			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{	SOCK_FLOAT, 1, N_("Blackbody Intensity"),	0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, PROP_FACTOR},
	{	SOCK_RGBA, 1, N_("Blackbody Tint"),			1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f},
	{	SOCK_FLOAT, 1, N_("Temperature"),			1000.0f, 0.0f, 0.0f, 0.0f, 0.0f, 6500.0f},
	{	SOCK_STRING, 1, N_("Temperature Attribute"), 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f},
	{	-1, 0, ""	}
};

static bNodeSocketTemplate sh_node_volume_principled_out[] = {
	{	SOCK_SHADER, 0, N_("Volume")},
	{	-1, 0, ""	}
};

static void node_shader_init_volume_principled(bNodeTree *UNUSED(ntree), bNode *node)
{
	for (bNodeSocket *sock = node->inputs.first; sock; sock = sock->next) {
		if (STREQ(sock->name, "Density Attribute")) {
			strcpy(((bNodeSocketValueString *)sock->default_value)->value, "density");
		}
		else if (STREQ(sock->name, "Temperature Attribute")) {
			strcpy(((bNodeSocketValueString *)sock->default_value)->value, "temperature");
		}
	}
}

static int node_shader_gpu_volume_principled(GPUMaterial *UNUSED(mat), bNode *UNUSED(node), bNodeExecData *UNUSED(execdata), GPUNodeStack *UNUSED(in), GPUNodeStack *UNUSED(out))
{
	return false;
}

/* node type definition */
void register_node_type_sh_volume_principled(void)
{
	static bNodeType ntype;

	sh_node_type_base(&ntype, SH_NODE_VOLUME_PRINCIPLED, "Principled Volume", NODE_CLASS_SHADER, 0);
	node_type_compatibility(&ntype, NODE_NEW_SHADING);
	node_type_socket_templates(&ntype, sh_node_volume_principled_in, sh_node_volume_principled_out);
	node_type_size_preset(&ntype, NODE_SIZE_LARGE);
	node_type_init(&ntype, node_shader_init_volume_principled);
	node_type_storage(&ntype, "", NULL, NULL);
	node_type_gpu(&ntype, node_shader_gpu_volume_principled);

	nodeRegisterType(&ntype);
}
