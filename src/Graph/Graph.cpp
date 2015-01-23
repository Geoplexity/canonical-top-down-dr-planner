

#include "Graph.hpp"



// #include <boost/graph/topological_sort.hpp>


#include <boost/graph/copy.hpp>



// for layout
#include <boost/config.hpp>
// #include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/simple_point.hpp>
#include <boost/property_map/property_map.hpp>


#include <boost/graph/circle_layout.hpp>
#include <boost/graph/kamada_kawai_spring_layout.hpp>

#include <boost/graph/random_layout.hpp>
#include <boost/graph/fruchterman_reingold.hpp>


#include <boost/graph/graphviz.hpp>

#include <boost/graph/iteration_macros.hpp>



#include <iostream>
#include <fstream>
#include <map>
#include <vector>

// #include <cstring>



// Graph::Graph(const Graph& other) {
//     // // boost::copy_graph<Graph, Graph>(other, *this);



//     // typedef std::map<Vertex_ID, size_t> IndexMap;
//     // IndexMap mapIndex;
//     // boost::associative_property_map<IndexMap> propmapIndex(mapIndex);

//     // int i=0;
//     // std::pair<Vertex_Iterator, Vertex_Iterator> vs = other.vertices();
//     // for (Vertex_Iterator it = vs.first; it != vs.second; it++)
//     // {
//     //     put(propmapIndex, *it, i++);
//     // }

//     // this->clear();
//     // boost::copy_graph(other, *this, vertex_index_map( propmapIndex ) );




//     this->clear();

//     std::vector<Vertex_ID> verts;

//     std::pair<Vertex_Iterator, Vertex_Iterator> vs = other.vertices();
//     for (Vertex_Iterator it = vs.first; it != vs.second; it++)
//     {
//         verts.push_back(this->add_vertex(other[*it]));
//     }

//     std::pair<Edge_Iterator, Edge_Iterator> es = other.edges();
//     for (Edge_Iterator it = es.first; it != es.second; it++)
//     {
//         std::pair<Vertex_ID, Vertex_ID> vs_on_e = verts_on_edge(it);
//         this->add_edge(vs_on_e.first, vs_on_e.second, other[*it]);
//     }
// }



Vertex_ID Graph::add_vertex(Vertex_Properties vp) {
    return this->Graph_Type::add_vertex(vp);
}

Vertex_ID Graph::add_vertex() {
    return this->add_vertex(Vertex_Properties());
}

Edge_ID Graph::add_edge(Vertex_ID v0, Vertex_ID v1, Edge_Properties ep) {
    std::pair<Edge_ID, bool> p = this->Graph_Type::add_edge(v0, v1, ep);
    Edge_ID e = p.first;
    bool success = p.second;

    if (success) {
        //
    } else {
        //
    }

    return e;
}

Edge_ID Graph::add_edge(Vertex_ID v0, Vertex_ID v1, double distance) {
    return this->add_edge(v0, v1, Edge_Properties(distance));
}

std::pair<Vertex_Iterator, Vertex_Iterator> Graph::vertices() const {
    return boost::vertices(*this);
}

std::pair<Edge_Iterator, Edge_Iterator> Graph::edges() const {
    return boost::edges(*this);
}

Vertex_Iterator Graph::find_vertex(const char *name) const {
    Vertex_Iterator v, v_end;
    for (boost::tie(v, v_end) = this->vertices(); v != v_end; v++) {
        if ((*this)[*v].name.compare(name) == 0) {
            return v;
        }
    }

    return v_end;
}


unsigned int Graph::num_vertices() const {
    return boost::num_vertices(*this);
}

unsigned int Graph::num_edges() const {
    return boost::num_edges(*this);
}

std::pair<Vertex_ID, Vertex_ID> Graph::verts_on_edge(Edge_ID e) const {
    return std::make_pair(boost::source(e, *this), boost::target(e, *this));
}




void Graph::set_layout() {
    typedef boost::property_map<Graph_Type, Point Vertex_Properties::*>::type Vertex_Point_Map;
    typedef boost::property_map<Graph_Type, double Edge_Properties::*>::type Edge_Distance_Map;


    Vertex_Point_Map vp_map = boost::get(&Vertex_Properties::point, *this);
    Edge_Distance_Map ed_map = boost::get(&Edge_Properties::length, *this);

    boost::circle_graph_layout(*this, vp_map, 100);
    boost::kamada_kawai_spring_layout(
        *this,
        vp_map,
        ed_map,
        boost::square_topology<>(),
        boost::side_length<double>(0.4)
        // boost::layout_tolerance<>(),
        // 1,
        // vertexIdPropertyMap
        );

    // boost::random_graph_layout(*this, vp_map, boost::square_topology<>());
    // boost::fruchterman_reingold_force_directed_layout(
    //     *this,
    //     vp_map,
    //     boost::square_topology<>());


    Vertex_Iterator i, end;
    for (boost::tie(i, end) = this->vertices(); i != end; i++) {
        (*this)[*i].x = vp_map[*i][0];
        (*this)[*i].y = vp_map[*i][1];
    }
}


// TODO: Potentially scale edge length
void Graph::get_graph_in_range(float x_min, float x_max, float y_min, float y_max) {
    // Vertex_Iterator v, v_end;
    // boost::tie(v, v_end) = vertices();

    // float
    //     min_x_seen = (*this)[*v].x,
    //     max_x_seen = (*this)[*v].x,
    //     min_y_seen = (*this)[*v].y,
    //     max_y_seen = (*this)[*v].y;

    // v++;
    // for (; v != v_end; v++) {
    //     float v_x = (*this)[*v].x, v_y = (*this)[*v].y;
    //     if ()
    //     add_vertex(*v_it);
    // }

    float
        del_x = x_max - x_min,
        del_y = y_max - y_min;




    Vertex_Iterator v, end;
    boost::tie(v, end) = this->vertices();
    double
        maxx = (*this)[*v].x,
        minx = (*this)[*v].x,
        maxy = (*this)[*v].y,
        miny = (*this)[*v].y;
    // double centerx=0, centery=0;

    for (; v != end; v++) {
        double x = (*this)[*v].x;
        double y = (*this)[*v].y;

        // centerx += x; centery += y;

        maxx = (x > maxx)? x: maxx;
        maxy = (y > maxy)? y: maxy;

        minx = (x < minx)? x: minx;
        miny = (y < miny)? y: miny;
    }


    // centerx /= this->num_vertices();
    // centery /= this->num_vertices();

    // maxx -= centerx; minx -= centerx;
    // maxy -= centery; miny -= centery;

    double
        centerx = minx + (maxx - minx)/2,
        centery = miny + (maxy - miny)/2;

    maxx -= centerx; minx -= centerx;
    maxy -= centery; miny -= centery;


    double
        diff_x = (maxx > -minx)? maxx: -minx,
        diff_y = (maxy > -miny)? maxy: -miny,
        scale_x = del_x/2/diff_x,
        scale_y = del_y/2/diff_y,
        scale = (scale_x < scale_y)? scale_x: scale_y;

    for (boost::tie(v, end) = this->vertices(); v != end; v++) {
        (*this)[*v].x = ((*this)[*v].x - centerx) * scale;
        (*this)[*v].y = ((*this)[*v].y - centery) * scale;
    }
}


void Graph::write_to_file(const char* filename) {
    std::ofstream f(filename);
    boost::write_graphviz(f, *this);
}

// #include <boost/graph/property_maps/null_property_map.hpp>
void Graph::read_from_file(const char* filename) {
    boost::dynamic_properties dp;

    // vertex properties
    dp.property("node_id", boost::get(&Vertex_Properties::name, *this));
    // boost::make_null_property<Vertex_ID, std::string>
    dp.property("x", boost::get(&Vertex_Properties::x, *this));
    dp.property("y", boost::get(&Vertex_Properties::y, *this));

    // edge properties
    dp.property("length", boost::get(&Edge_Properties::length, *this));

    // read in
    std::ifstream f(filename);
    boost::read_graphviz(f, *this, dp);
}









// template <class WeightMap,class CapacityMap>
// class edge_writer {
// public:
//   edge_writer(WeightMap w, CapacityMap c) : wm(w),cm(c) {}
//   template <class Edge>
//   void operator()(ostream &out, const Edge& e) const {
//     out << "[label=\"" << wm[e] << "\", taillabel=\"" << cm[e] << "\"]";
//   }
// private:
//   WeightMap wm;
//   CapacityMap cm;
// };

// template <class WeightMap, class CapacityMap>
// inline edge_writer<WeightMap,CapacityMap>
// make_edge_writer(WeightMap w,CapacityMap c) {
//   return edge_writer<WeightMap,CapacityMap>(w,c);
// }

// ofstream dot("graph.dot");
// write_graphviz(dot, g,
//   boost::make_label_writer(boost::get(&vert::name, g)),
//   make_edge_writer(boost::get(&edge::weight,g),boost::get(&edge::capacity,g)));



















// #include <boost/graph/fruchterman_reingold.hpp>
// #include <boost/graph/random_layout.hpp>
// #include <boost/graph/kamada_kawai_spring_layout.hpp>
// #include <boost/graph/circle_layout.hpp>
// #include <boost/graph/adjacency_list.hpp>
// #include <boost/graph/point_traits.hpp>
// #include <boost/random/linear_congruential.hpp>
// #include <boost/test/minimal.hpp>
// #include <iostream>
// #include <boost/limits.hpp>
// #include <fstream>
// #include <string>
// using namespace boost;

// enum vertex_position_t { vertex_position };
// namespace boost { BOOST_INSTALL_PROPERTY(vertex, position); }

// typedef square_topology<>::point_type point;

// template<typename Graph, typename PositionMap, typename Topology>
// void print_graph_layout(const Graph& g, PositionMap position, const Topology& topology)
// {
//   typedef typename Topology::point_type Point;
//   // Find min/max ranges
//   Point min_point = position[*vertices(g).first], max_point = min_point;
//   BGL_FORALL_VERTICES_T(v, g, Graph) {
//     min_point = topology.pointwise_min(min_point, position[v]);
//     max_point = topology.pointwise_max(max_point, position[v]);
//   }

//   for (int y = (int)min_point[1]; y <= (int)max_point[1]; ++y) {
//     for (int x = (int)min_point[0]; x <= (int)max_point[0]; ++x) {
//       typename graph_traits<Graph>::vertex_Iteratorator vi, vi_end;
//       // Find vertex at this position
//       typename graph_traits<Graph>::vertices_size_type index = 0;
//       for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi, ++index) {
//         if ((int)position[*vi][0] == x && (int)position[*vi][1] == y)
//           break;
//       }

//       if (vi == vi_end) std::cout << ' ';
//       else std::cout << (char)(index + 'A');
//     }
//     std::cout << std::endl;
//   }
// }

// template<typename Graph, typename PositionMap>
// void dump_graph_layout(std::string name, const Graph& g, PositionMap position)
// {
//   std::ofstream out((name + ".dot").c_str());
//   out << "graph " << name << " {" << std::endl;

//   typename graph_traits<Graph>::vertex_Iteratorator vi, vi_end;
//   for (tie(vi, vi_end) = vertices(g); vi != vi_end; ++vi) {
//     out << "  n" << get(vertex_index, g, *vi) << "[ pos=\""
//         << (int)position[*vi][0] + 25 << ", " << (int)position[*vi][1] + 25
//         << "\" ];\n";
//   }

//   typename graph_traits<Graph>::edge_Iteratorator ei, ei_end;
//   for (tie(ei, ei_end) = edges(g); ei != ei_end; ++ei) {
//     out << "  n" << get(vertex_index, g, source(*ei, g)) << " -- n"
//         << get(vertex_index, g, target(*ei, g)) << ";\n";
//   }
//   out << "}\n";
// }

// template<typename Graph>
// void
// test_circle_layout(Graph*, typename graph_traits<Graph>::vertices_size_type n)
// {
//   typedef typename graph_traits<Graph>::vertex_descriptor vertex;
//   typedef typename graph_traits<Graph>::vertex_Iteratorator vertex_Iteratorator;
//   typedef typename graph_traits<Graph>::vertices_size_type vertices_size_type;
//   typedef typename graph_traits<Graph>::edges_size_type edges_size_type;

//   Graph g(n);

//   // Initialize vertex indices
//   vertex_Iteratorator vi = vertices(g).first;
//   for (vertices_size_type i = 0; i < n; ++i, ++vi)
//     put(vertex_index, g, *vi, i);

//   circle_graph_layout(g, get(vertex_position, g), 10.0);

//   std::cout << "Regular polygon layout with " << n << " points.\n";
//   square_topology<> topology;
//   print_graph_layout(g, get(vertex_position, g), topology);
// }

// struct simple_edge
// {
//   int first, second;
// };

// struct kamada_kawai_done
// {
//   kamada_kawai_done() : last_delta() {}

//   template<typename Graph>
//   bool operator()(double delta_p,
//                   typename boost::graph_traits<Graph>::vertex_descriptor /*p*/,
//                   const Graph& /*g*/,
//                   bool global)
//   {
//     if (global) {
//       double diff = last_delta - delta_p;
//       if (diff < 0) diff = -diff;
//       last_delta = delta_p;
//       return diff < 0.01;
//     } else {
//       return delta_p < 0.01;
//     }
//   }

//   double last_delta;
// };

// template<typename Graph>
// void
// test_triangle(Graph*)
// {
//   typedef typename graph_traits<Graph>::vertex_descriptor vertex_descriptor;
//   typedef typename graph_traits<Graph>::edge_descriptor edge_descriptor;

//   Graph g;

//   vertex_descriptor u = add_vertex(g); put(vertex_index, g, u, 0);
//   vertex_descriptor v = add_vertex(g); put(vertex_index, g, v, 1);
//   vertex_descriptor w = add_vertex(g); put(vertex_index, g, w, 2);

//   edge_descriptor e1 = add_edge(u, v, g).first; put(edge_weight, g, e1, 1.0);
//   edge_descriptor e2 = add_edge(v, w, g).first; put(edge_weight, g, e2, 1.0);
//   edge_descriptor e3 = add_edge(w, u, g).first; put(edge_weight, g, e3, 1.0);

//   circle_graph_layout(g, get(vertex_position, g), 25.0);

//   bool ok = kamada_kawai_spring_layout(g,
//                                        get(vertex_position, g),
//                                        get(edge_weight, g),
//                                        square_topology<>(50.0),
//                                        side_length(50.0));
//   BOOST_CHECK(ok);

//   std::cout << "Triangle layout (Kamada-Kawai).\n";
//   print_graph_layout(g, get(vertex_position, g));
// }







Subgraph::Subgraph(const Graph *g) {
    _graph = g;
}

const Graph* Subgraph::graph() {
    return _graph;
}

// void Subgraph::induce(Vertex_Iterator begin, Vertex_Iterator end) {
//     for (Vertex_Iterator v_it = begin; v_it != end; v_it++) {
//         _vertices.insert(*v_it);
//     }


//     std::pair<Edge_Iterator, Edge_Iterator> es = _graph->edges();
//     for (Edge_Iterator e_it = es.first; e_it != es.second; e_it++) {
//         std::pair<Vertex_ID, Vertex_ID> vs = _graph->verts_on_edge(e_it);
//         if (_vertices.find(vs.first) != _vertices.end()
//             && _vertices.find(vs.second) != _vertices.end())
//         {
//             _edges.insert(*e_it);
//         }
//     }
// }

// void Subgraph::induce(std::set<Vertex_ID> *vertices) {
//     for (Vertex_Iterator v_it = begin; v_it != end; v_it++) {
//         _vertices.insert(*v_it);
//     }


//     std::pair<Edge_Iterator, Edge_Iterator> es = _graph->edges();
//     for (Edge_Iterator e_it = es.first; e_it != es.second; e_it++) {
//         std::pair<Vertex_ID, Vertex_ID> vs = _graph->verts_on_edge(e_it);
//         if (_vertices.find(vs.first) != _vertices.end()
//             && _vertices.find(vs.second) != _vertices.end())
//         {
//             _edges.insert(*e_it);
//         }
//     }
// }

void Subgraph::induce(Vertex_Iterator begin, Vertex_Iterator end) {
    for (Vertex_Iterator v_it = begin; v_it != end; v_it++)
        add_vertex(*v_it);
}

void Subgraph::induce(std::set<Vertex_ID> *vertices) {
    for (std::set<Vertex_ID>::iterator v_it = vertices->begin();
        v_it != vertices->end(); v_it++)
    {
        add_vertex(*v_it);
    }
}

void Subgraph::add_vertex(Vertex_ID vertex) {
    _vertices.insert(vertex);

    boost::graph_traits<Graph>::adjacency_iterator v, v_end;
    for (boost::tie(v, v_end) = boost::adjacent_vertices(vertex, *_graph);
        v != v_end; v++)
    {
        if (_vertices.find(*v) != _vertices.end()) {
            Edge_ID e = boost::edge(vertex, *v, *_graph).first;
            _edges.insert(e);
        }
    }
}

void Subgraph::remove_vertex(Vertex_ID vertex) {
    _vertices.erase(vertex);

    boost::graph_traits<Graph>::adjacency_iterator v, v_end;
    for (boost::tie(v, v_end) = boost::adjacent_vertices(vertex, *_graph);
        v != v_end; v++)
    {
        Edge_ID e = boost::edge(vertex, *v, *_graph).first;
        _edges.erase(e);
    }
}


// void Subgraph::add_vertex(Vertex_ID vertex) {
//     _vertices.insert(vertex);

//     // check all the edges. if they are
//     boost::graph_traits<Graph>::out_edge_iterator e, e_end;
//     boost::tie(e, e_end) = boost::out_edges(vertex, *_graph);
//     for (; e != e_end; e++) {
//         std::pair<Vertex_ID, Vertex_ID> vs = _graph->verts_on_edge(*e);
//         Vertex_ID v = (vs.first==vertex)? vs.first: vs.second;
//         if (_vertices.find(v) != _vertices.end()) {
//             _edges.insert(*e);
//         }
//     }
// }


std::pair<Sg_Vertex_Iterator, Sg_Vertex_Iterator> Subgraph::vertices() {
    return std::pair<Sg_Vertex_Iterator, Sg_Vertex_Iterator>(_vertices.begin(), _vertices.end());
}

std::pair<Sg_Edge_Iterator, Sg_Edge_Iterator> Subgraph::edges() {
    return std::pair<Sg_Edge_Iterator, Sg_Edge_Iterator>(_edges.begin(), _edges.end());
}

std::set<Vertex_ID> Subgraph::vertices_adjacent(std::set<Vertex_ID> &v_set) {
    std::set<Vertex_ID> ret;
    for (std::set<Vertex_ID>::iterator set_v = v_set.begin(); set_v != v_set.end(); set_v++) {
        boost::graph_traits<Graph>::adjacency_iterator v, v_end;
        for (boost::tie(v, v_end) = boost::adjacent_vertices(*set_v, *_graph);
            v != v_end; v++)
        {
            ret.insert(*v);
        }
    }

    return ret;
}

// assumes they're disjoint
std::vector<std::set<Vertex_ID> > Subgraph::edges_between(
        std::set<Vertex_ID> &v_set_1,
        std::set<Vertex_ID> &v_set_2)
{
    std::vector<std::set<Vertex_ID> > ret;
    for (std::set<Vertex_ID>::iterator set_v = v_set_1.begin(); set_v != v_set_1.end(); set_v++) {
        std::set<Vertex_ID> adjacent_vs;
        boost::graph_traits<Graph>::adjacency_iterator v, v_end;
        for (boost::tie(v, v_end) = boost::adjacent_vertices(*set_v, *_graph);
            v != v_end; v++)
        {
            if (v_set_2.find(*v) != v_set_2.end()) {
                std::set<Vertex_ID> add_to;
                add_to.insert(*v);
                add_to.insert(*set_v);
                ret.push_back(add_to);
            }
        }
    }

    return ret;
}


// const std::set<Vertex_ID>* Subgraph::vertices() {return &_vertices; }
// const std::set<Edge_ID>* Subgraph::edges() {return &_edges; }

std::pair<Vertex_ID, Vertex_ID> Subgraph::verts_on_edge(Edge_ID e) {
    return _graph->verts_on_edge(e);
}


unsigned int Subgraph::num_vertices() {
    return _vertices.size();
}

unsigned int Subgraph::num_edges() {
    return _edges.size();
}


const Vertex_Properties& Subgraph::operator[](Vertex_ID vertex) {
    return (*_graph)[vertex];
}
