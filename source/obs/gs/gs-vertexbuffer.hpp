/*
 * Modern effects for a modern Streamer
 * Copyright (C) 2017 Michael Fabian Dirks
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#pragma once
#include "common.hpp"
#include "gs-limits.hpp"
#include "gs-vertex.hpp"
#include "utility.hpp"

namespace gs {
	class vertex_buffer {
		uint32_t _capacity;
		uint32_t _size;
		uint8_t  _layers;

		// OBS GS Data
		std::shared_ptr<gs_vertbuffer_t> _buffer;
		std::shared_ptr<gs_vb_data>      _data;

		// Memory Storage
		vec3*          _positions;
		vec3*          _normals;
		vec3*          _tangents;
		uint32_t*      _colors;
		gs_tvertarray* _uv_layers;
		vec4*          _uvs[MAXIMUM_UVW_LAYERS];

		// OBS compatability
		gs_vb_data* _obs_data;

		void initialize(uint32_t capacity, uint8_t layers);
		void finalize();

		public:
		virtual ~vertex_buffer();

		/*!
		* \brief Create a Vertex Buffer with the default number of Vertices.
		*/
		vertex_buffer() : vertex_buffer(MAXIMUM_VERTICES, MAXIMUM_UVW_LAYERS) {}

		/*!
		* \brief Create a Vertex Buffer with a specific number of Vertices.
		*
		* \param vertices Number of vertices to store.
		*/
		vertex_buffer(uint32_t vertices) : vertex_buffer(vertices, MAXIMUM_UVW_LAYERS) {}

		/*!
		* \brief Create a Vertex Buffer with a specific number of Vertices and uv layers.
		*
		* \param vertices Number of vertices to store.
		* \param layers Number of uv layers to store.
		*/
		vertex_buffer(uint32_t vertices, uint8_t layers);

		/*!
		* \brief Create a copy of a Vertex Buffer
		* Full Description below
		*
		* \param other The Vertex Buffer to copy
		*/
		vertex_buffer(gs_vertbuffer_t* other);

		// Copy Constructor & Assignments

		/*!
		* \brief Copy Constructor
		* 
		*
		* \param other 
		*/
		vertex_buffer(vertex_buffer const& other);

		/*!
		* \brief Copy Assignment
		* Unsafe operation and as such marked as deleted.
		*
		* \param other
		*/
		void operator=(vertex_buffer const& other);

		// Move Constructor & Assignments

		/*!
		* \brief Move Constructor
		*
		*
		* \param other
		*/
		vertex_buffer(vertex_buffer const&& other) noexcept;

		/*!
		* \brief Move Assignment
		*
		*
		* \param other
		*/
		void operator=(vertex_buffer const&& other);

		void resize(uint32_t new_size);

		uint32_t size();

		uint32_t capacity();

		bool empty();

		const gs::vertex at(uint32_t idx);

		const gs::vertex operator[](uint32_t const pos);

		void set_uv_layers(uint8_t layers);

		uint8_t get_uv_layers();

		/*!
		* \brief Directly access the positions buffer
		* Returns the internal memory that is assigned to hold all vertex positions.
		*
		* \return A <vec3*> that points at the first vertex's position.
		*/
		vec3* get_positions();

		/*!
		* \brief Directly access the normals buffer
		* Returns the internal memory that is assigned to hold all vertex normals.
		*
		* \return A <vec3*> that points at the first vertex's normal.
		*/
		vec3* get_normals();

		/*!
		* \brief Directly access the tangents buffer
		* Returns the internal memory that is assigned to hold all vertex tangents.
		*
		* \return A <vec3*> that points at the first vertex's tangent.
		*/
		vec3* get_tangents();

		/*!
		* \brief Directly access the colors buffer
		* Returns the internal memory that is assigned to hold all vertex colors.
		*
		* \return A <uint32_t*> that points at the first vertex's color.
		*/
		uint32_t* get_colors();

		/*!
		* \brief Directly access the uv buffer
		* Returns the internal memory that is assigned to hold all vertex uvs.
		*
		* \return A <vec4*> that points at the first vertex's uv.
		*/
		vec4* get_uv_layer(uint8_t idx);

		gs_vertbuffer_t* update();

		gs_vertbuffer_t* update(bool refreshGPU);
	};
} // namespace gs
