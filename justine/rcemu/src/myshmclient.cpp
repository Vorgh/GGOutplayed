/**
 * @brief Justine - this is a rapid prototype for development of Robocar City Emulator
 *
 * @file myshmclient.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 0.0.10
 *
 * @section LICENSE
 *
 * Copyright (C) 2014 Norbert Bátfai, batfai.norbert@inf.unideb.hu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * Robocar City Emulator and Robocar World Championship
 *
 * desc
 *
 */

#include <myshmclient.hpp>
//#include <trafficlexer.hpp>
#include <fstream>

char data[524288];

std::vector<justine::sampleclient::MyShmClient::Gangster> justine::sampleclient::MyShmClient::gangsters ( boost::asio::ip::tcp::socket & socket, int id,
        osmium::unsigned_object_id_type cop )
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data, "<gangsters " );
    length += std::sprintf ( data + length, "%d>", id );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );

    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );
    }

    /* reading all gangsters into a vector */
    int idd {0};
    unsigned f, t, s;
    int n {0};
    int nn {0};
    std::vector<Gangster> gangsters;

    while ( std::sscanf ( data + nn, "<OK %d %u %u %u>%n", &idd, &f, &t, &s, &n ) == 4 )
    {
        nn += n;
        gangsters.push_back ( Gangster {idd, f, t, s} );
    }

    /*std::sort ( gangsters.begin(), gangsters.end(), [this, cop] ( Gangster x, Gangster y )
    {
        return dst ( cop, x.to ) < dst ( cop, y.to );
    } );*/

    std::cout.write ( data, length );
    std::cout << "Command GANGSTER sent." << std::endl;

    return gangsters;
}

std::vector<justine::sampleclient::MyShmClient::Cop> justine::sampleclient::MyShmClient::initcops ( boost::asio::ip::tcp::socket & socket, int number )
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data, "<init guided %s %d c>", m_teamname.c_str(), number );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );


    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );
    }

    /* reading all gangsters into a vector */
    int idd {0};
    int f, t;
    char c;
    int n {0};
    int nn {0};
    std::vector<Cop> cops;

    while ( std::sscanf ( data + nn, "<OK %d %d/%d %c>%n", &idd, &f, &t, &c, &n ) == 4 )
    {
        nn += n;
        cops.push_back ( idd );
    }

    std::cout.write ( data, length );
    std::cout << "Command INIT sent." << std::endl;

    return cops;
}


int justine::sampleclient::MyShmClient::init ( boost::asio::ip::tcp::socket & socket )
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data, "<init guided %s 1 c>", m_teamname.c_str() );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );

    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );

    }

    int id {0};
    std::sscanf ( data, "<OK %d", &id );

    std::cout.write ( data, length );
    std::cout << "Command INIT sent." << std::endl;

    return id;

}

void justine::sampleclient::MyShmClient::pos ( boost::asio::ip::tcp::socket & socket, int id )
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data, "<pos " );
    length += std::sprintf ( data + length, "%d %u %u>", id, 2969934868u, 651365957u );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );

    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );

    }

    std::cout.write ( data, length );
    std::cout << "Command POS sent." << std::endl;
}

void justine::sampleclient::MyShmClient::car ( boost::asio::ip::tcp::socket & socket, int id, unsigned *f, unsigned *t, unsigned* s )
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data, "<car " );
    length += std::sprintf ( data + length, "%d>", id );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );

    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );
    }

    int idd {0};
    std::sscanf ( data, "<OK %d %u %u %u", &idd, f, t, s );

    std::cout.write ( data, length );
    std::cout << "Command CAR sent." << std::endl;

}

void justine::sampleclient::MyShmClient::route (
    boost::asio::ip::tcp::socket & socket,
    int id,
    std::vector<osmium::unsigned_object_id_type> & path
)
{

    boost::system::error_code err;

    size_t length = std::sprintf ( data,
                                   "<route %d %d", path.size(), id );

    for ( auto ui : path )
        length += std::sprintf ( data + length, " %u", ui );

    length += std::sprintf ( data + length, ">" );

    socket.send ( boost::asio::buffer ( data, length ) );

    length = socket.read_some ( boost::asio::buffer ( data ), err );

    if ( err == boost::asio::error::eof )
    {

        // TODO

    }
    else if ( err )
    {

        throw boost::system::system_error ( err );

    }

    std::cout.write ( data, length );
    std::cout << "Command ROUTE sent." << std::endl;

}

/*void justine::sampleclient::MyShmClient::start ( boost::asio::io_service& io_service, const char * port )
{

#ifdef DEBUG
  foo();
#endif

  boost::asio::ip::tcp::resolver resolver ( io_service );
  boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
  boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

  boost::asio::ip::tcp::socket socket ( io_service );
  boost::asio::connect ( socket, iterator );

  int id = init ( socket );

  pos ( socket, id );

  unsigned int g {0u};
  unsigned int f {0u};
  unsigned int t {0u};
  unsigned int s {0u};

  std::vector<Gangster> gngstrs;

  for ( ;; )
    {
      std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) );

      car ( socket, id, &f, &t, &s );

      gngstrs = gangsters ( socket, id, t );

      if ( gngstrs.size() > 0 )
        g = gngstrs[0].to;
      else
        g = 0;
      if ( g > 0 )
        {

          std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );

          if ( path.size() > 1 )
            {

              std::copy ( path.begin(), path.end(),
                          std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );

              route ( socket, id, path );
            }
        }
    }
}
*/

void justine::sampleclient::MyShmClient::start ( boost::asio::io_service& io_service, const char * port, int number )
{

#ifdef DEBUG
    foo();
#endif

    boost::asio::ip::tcp::resolver resolver ( io_service );
    boost::asio::ip::tcp::resolver::query query ( boost::asio::ip::tcp::v4(), "localhost", port );
    boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve ( query );

    boost::asio::ip::tcp::socket socket ( io_service );
    boost::asio::connect ( socket, iterator );

    std::vector<Cop> cops = initcops ( socket, number );

    unsigned int g {0u};
    unsigned int f {0u};
    unsigned int t {0u};
    unsigned int s {0u};

    std::vector<Gangster> gngstrs;

    std::vector<std::vector<std::vector<double>>> database;
    int checktimer = 0;
    int presize = 0;

    for ( ;; )
    {
        std::this_thread::sleep_for ( std::chrono::milliseconds ( 200 ) );

        for ( int i = 0; i < cops.size(); i++ )
        {
            car ( socket, cops[i], &f, &t, &s );
            gngstrs = gangsters ( socket, cops[i], t );

            if ( gngstrs.size() > 0 )
            {
		if (gngstrs.size() != presize)
		{
		    database.clear();
		    database.resize(cops.size());
		    for (int j=0; j<cops.size(); j++)
		    {
			database[j].resize(gngstrs.size());
			for (int k=0; k<gngstrs.size(); k++)
			{
			    database[j][k].resize(5);
			}
		    }
		    presize = gngstrs.size();
		    checktimer = 0;
		}
		
                if ( checktimer < 5 )
                {
                    for ( int k = 0; k < gngstrs.size(); k++ )
                    {
                        Gangster gng = gngstrs[k];
                        database[i][k].push_back ( dst ( gng.to, t ) );
                    }
                    
                    std::vector<Gangster> tmp_gngstrs = gngstrs;
                    std::sort ( tmp_gngstrs.begin(), tmp_gngstrs.end(), [this, t] ( Gangster x, Gangster y )
		    {
			return dst ( t, x.to ) < dst ( t, y.to );
		    } );
		    
		    g = tmp_gngstrs[0].to;
                }
                else
                {
		    double maxpriority = 10000;
		    int g_id = 0;
		    double priority;
		    std::vector<double> vect;
		    vect.resize(5);
		    
                    for ( int j = 0; j < gngstrs.size(); j++ )
                    {
			Gangster gng = gngstrs[j];
			vect = database[i][j];
			double distance = dst(t, gng.to);
                        priority = distance - (vect.front() - distance);
			if (priority < maxpriority)
			{
			    maxpriority = priority;
			    g_id = j;
			}
			
			std::rotate(vect.begin(),vect.begin()+1,vect.end());
			vect.back() = distance;
			database[i][j] = vect;
			
                    }
                    g = gngstrs[g_id].to; 
                }
            }
            else
                g = 0;

            if ( g > 0 )
            {
                std::vector<osmium::unsigned_object_id_type> path = hasDijkstraPath ( t, g );

                if ( path.size() > 1 )
                {
                    std::copy ( path.begin(), path.end(),
                                std::ostream_iterator<osmium::unsigned_object_id_type> ( std::cout, " -> " ) );

                    route ( socket, cops[i], path );
                }
            }
        }
        checktimer++;
    }
}

/*int justine::sampleclient::MyShmClient::DistanceDifference ( std::map<int, double[5]> distances )
{
    double difference = 0;
    double maxdifference = 0;
    int returnkey = -1;

    for ( auto const & i : distances )
    {
        double max = i.second[0];
        double min = i.second[0];

        for ( int j = 1; j < i.second.size(); j++ )
        {
            if ( i.second[j] > max )
                max = i.second[j];

            if ( i.second[j] < min )
                min = i.second[j];
        }

        difference = max - min;

        if ( difference > maxdifference )
        {
            maxdifference = difference;
            returnkey = i.first;
        }
    }

    return returnkey;
}*/
