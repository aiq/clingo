#!/usr/bin/env lua

--------------------------------------------------------------------------------
--LuaZDF-begin --with append appendall basename buildset capexec currentdir dirname
--+ endswith filelist findup isdir joinpath keys mint readfile readlines
--+ relativepath rmsuffix splitpath startswith writefile
--------------------------------------------------------------------------------
local lfs = require( "lfs" ) --ZREQ-lfs
--ZFUNC-currentdir-v1
local function currentdir() --> path
   --ZFUNC-unixpath-v1
   local function unixpath( path )
      return path:gsub( "\\", "/" )
   end
   local path = lfs.currentdir()
   return unixpath( path )
end
--ZFUNC-dirname-v1
local function dirname( path ) --> parent
   local i = #path
   local c = string.sub( path, i, i )
   if c == "/" and #path >= 1 then
      i = i - 1
      c = string.sub( path, i, i )
   end
   
   while i > 0 and c ~= "/" do
      i = i - 1
      c = string.sub( path, i, i )
   end
   if i == 0 then 
      return path
   elseif i == 1 then -- root case
      return string.sub( path, 1, 1 )
   else
      return string.sub( path, 1, i-1 )
   end
end
--ZFUNC-isdir-v1
local function isdir( path ) --> res
   local mode = lfs.attributes( path, "mode" )
   if mode == "directory" then
      return true
   else
      return false
   end
end
--ZFUNC-joinpath-v1
local function joinpath( tab ) --> path
   --ZFUNC-firstchar-v1
   local function firstchar( str )
      return string.sub( str, 1, 1 )
   end
   --ZFUNC-lastchar-v1
   local function lastchar( str )
      return string.sub( str, #str )
   end
   local rooted = false
   local tmptab = {}
   for k, s in ipairs( tab ) do
      if k == 1 and firstchar( s ) == "/" then
         rooted = true
      end
      if firstchar( s ) == "/" then
         s = s:sub( 2 )
      end
      if lastchar( s ) == "/" then
         s = s:sub( 1, #s - 1 )
      end
      if #s > 0 then
         table.insert( tmptab, s )
      end
   end
   if rooted then
      return "/"..table.concat( tmptab, "/" )
   end
   return table.concat( tmptab, "/" )
end
--ZFUNC-readfile-v1
local function readfile( filename ) --> str, err
   local f, err = io.open( filename, "r" )
   if err then return nil, err end
   local str, err = f:read( "*a" )
   if err then return nil, err end
   local res, err = f:close()
   if err then return nil, err end
   return str
end
--ZFUNC-rmsuffix-v1
local function rmsuffix( str, suffix ) --> nstr
   local suffixlen = string.len( suffix )
   local endsub = string.sub( str, -suffixlen )
   if endsub == suffix then
      local n = string.len( str ) - suffixlen
      return string.sub( str, 1, n )
   else
      return str
   end
end
--ZFUNC-splitpath-v1
local function splitpath( path ) --> tab
   local tab = {}
   for token in string.gmatch( path, "[^/]+" ) do
      if #token > 0 then
         table.insert( tab, token )
      end
   end
   return tab
end
--ZFUNC-append-v1
local function append( arr, v, ... ) --> arr
   table.insert( arr, v )
   if ... then
      for i, o in ipairs{ ... } do
         table.insert( arr, o )
      end
   end
   return arr
end
--ZFUNC-appendall-v1
local function appendall( arr, oth ) --> arr
   for _, v in ipairs( oth ) do
      table.insert( arr, v )
   end
   return arr
end
--ZFUNC-basename-v1
local function basename( path, ext ) --> name
   local i = #path
   local c = string.sub( path, i, i )
   while i > 0 and c ~= "/" do
      i = i - 1
      c = string.sub( path, i, i )
   end
   local name = path
   if i ~= 0 then name = string.sub( path, i+1 ) end
   
   if ext then
      return rmsuffix( name, ext )
   else
      return name
   end
end
--ZFUNC-buildset-v1
local function buildset( arr )
   local res = {}
   for _, v in ipairs( arr ) do res[ v ] = true end
   return res
end
--ZFUNC-capexec-v1
local function capexec( cmd ) --> exit, signal, stdout, stderr
 
   local outfile = os.tmpname()
   local errfile = os.tmpname()
   cmd = cmd..[[ >"]]..outfile..[[" 2>"]]..errfile..[["]]
   local exit, signal = os.execute( cmd )
   local outcnt = readfile( outfile )
   local errcnt = readfile( errfile )
   os.remove( outfile )
   os.remove( errfile )
   return exit, signal, outcnt, errcnt
end
--ZFUNC-endswith-v1
local function endswith( str, suffix ) --> res
   return string.sub( str, -string.len( suffix ) ) == suffix
end
--ZFUNC-filelist-v1
local function filelist( tree, root )
   local list = {}
   for name, v in pairs( tree ) do
      if type( v ) == "table" then
         local path = root and root.."/"..name or name
         local sublist = filelist( v, path )
         for _, file in ipairs( sublist ) do
            table.insert( list, file )
         end
      elseif type( v ) == "string" and v ~= "" then
         local file = root and root.."/"..v or v
         table.insert( list, file )
      end
   end
   return list;
end
local findup = (function() 
--ZFUNC-dirhas-v1
local function dirhas( path, name, mode ) --> entrypath
   local modeval = lfs.attributes( path, "mode" )
   if modeval ~= "directory" then return nil end
   for entry in lfs.dir( path ) do
      if entry == name then
         local entrypath = path.."/"..entry
         if mode then
            local modeval = lfs.attributes( entrypath, "mode" )
            if modeval ~= mode then
               return nil
            end
         end
         return entrypath
      end
   end
   return nil
end
--ZFUNC-unixpath-v1
local function unixpath( path )
   return path:gsub( "\\", "/" )
end
--ZFUNC-rootprefix-v1
local function rootprefix( path )
   local remote = path:match[[^//%w+/]] or path:match[[^\\%w+\]]
   if remote then return remote end
   local unix = path:sub( 1, 1 )
   if unix == "/" then return unix end
   local win = path:match[=[^[a-zA-Z]:[\/]]=]
   if win then return win end
   return ""
end
--ZFUNC-isabsolute-v1
local function isabsolute( path ) --> res
   return rootprefix( path ) ~= ""
end
--ZFUNC-firstchar-v1
local function firstchar( str )
   return string.sub( str, 1, 1 )
end
--ZFUNC-lastchar-v1
local function lastchar( str )
   return string.sub( str, #str )
end
--ZFUNC-normpath-v1
local function normpath( dirty ) --> clean
   if dirty == "" then return "." end
   local rooted = dirty:sub( 1, 1 ) == "/"
   
   local dirtytab = splitpath( dirty )
   local cleantab = {}
   for k, v in ipairs( dirtytab ) do
      if v == "." then
      elseif v == ".." then
         table.remove( cleantab )
      elseif v == "" then
      else
         table.insert( cleantab, v )
      end
   end
  
   if rooted then
      return "/"..table.concat( cleantab, "/" )
   end
   return table.concat( cleantab, "/" )
end
--ZFUNC-abspath-v3
local function abspath( path ) --> abs
   if isabsolute( path ) then
      return normpath( path )
   end
   return normpath( joinpath{ currentdir(), path } )
end
--ZFUNC-findup-v1
local function findup( path, name, mode, depth ) --> entrypath
   if not isdir( path ) then return nil end
   local currdir = abspath( path )
   while not dirhas( currdir, name, mode ) do
      local parentdir = dirname( currdir )
      if parentdir == currdir then return nil end
      if depth then
         depth = depth-1
         if depth < 0 then return nil end
      end
      currdir = parentdir
   end
   return joinpath{ currdir, name }
end
return findup
end)()
--ZFUNC-keys-v1
local function keys( tab ) --> arr
   local arr = {}
   for k, v in pairs( tab ) do
      table.insert( arr, k )
   end
   return arr
end
--ZFUNC-mint-v0
local function mint( template, ename ) --> ( sandbox ) --> expstr, err
   if not ename then ename = '_o' end
   local function expr(e) return ' '..ename..'('..e..')' end
   
   local function compat_load( str, env )
      local chunkname = 'mint_script'
      local func, err
      if _VERSION ~= 'Lua 5.1' then
         func, err = load( str, chunkname, 't', env )
      else
         func, err = loadstring( str, chunkname)
         if func then setfenv( func, env ) end
      end
      return func, err
   end
   -- Generate a script that expands the template
   local script = template:gsub( '(.-)@(%b{})([^@]*)',
     function( prefix, code, suffix )
        prefix = expr( string.format( '%q', prefix ) )
        suffix = expr( string.format( '%q', suffix ) )
        code = code:sub( 2, #code-1 )
        if code:match( '^{.*}$' ) then
           return prefix .. code:sub( 2, #code-1 ) .. suffix
        else
           return prefix .. expr( code ) .. suffix
        end
     end
   )
   -- The generator must be run only if at least one @{} was found
   local run_generator = ( script ~= template )
   -- Return a function that executes the script with a custom environment
   return function( sandbox )
    if not run_generator then return script end
    local expstr = ''
    if 'table' ~= type( sandbox ) then
      return nil, "mint generator requires a sandbox"
    end
    local oldout = sandbox[ ename ]
    sandbox[ ename ] = function( out ) expstr = expstr..tostring(out) end
    local generate, err = compat_load( script, sandbox )
    if not generate or err then
       sandbox[ ename ] = oldout
       return nil, err..'\nTemplate script: [[\n'..script..'\n]]'
    end
    local ok, err = pcall(generate)
    sandbox[ ename ] = oldout
    if not ok or err then
       return nil, err..'\nTemplate script: [[\n'..script..'\n]]'
    end
    return expstr
  end
end
--ZFUNC-readlines-v1
local function readlines( filename ) --> strlst, err
   --ZFUNC-lines-v1
   local function lines( str )
      if not str:find( "\n$" ) then str = str.."\n" end
      return str:gmatch( "([^\n]*)\n" )
   end
   local f, err = io.open( filename, "r" )
   if err then return nil, err end
   local str, err = f:read( "*a" )
   if err then return nil, err end
   local strlst = {}
   for line in lines( str ) do
      table.insert( strlst, line )
   end
   local res, err = f:close()
   if err then return nil, err end
   return strlst
end
local relativepath = (function() 
--ZFUNC-unixpath-v1
local function unixpath( path )
   return path:gsub( "\\", "/" )
end
--ZFUNC-rootprefix-v1
local function rootprefix( path )
   local remote = path:match[[^//%w+/]] or path:match[[^\\%w+\]]
   if remote then return remote end
   local unix = path:sub( 1, 1 )
   if unix == "/" then return unix end
   local win = path:match[=[^[a-zA-Z]:[\/]]=]
   if win then return win end
   return ""
end
--ZFUNC-isabsolute-v1
local function isabsolute( path ) --> res
   return rootprefix( path ) ~= ""
end
--ZFUNC-firstchar-v1
local function firstchar( str )
   return string.sub( str, 1, 1 )
end
--ZFUNC-lastchar-v1
local function lastchar( str )
   return string.sub( str, #str )
end
--ZFUNC-normpath-v1
local function normpath( dirty ) --> clean
   if dirty == "" then return "." end
   local rooted = dirty:sub( 1, 1 ) == "/"
   
   local dirtytab = splitpath( dirty )
   local cleantab = {}
   for k, v in ipairs( dirtytab ) do
      if v == "." then
      elseif v == ".." then
         table.remove( cleantab )
      elseif v == "" then
      else
         table.insert( cleantab, v )
      end
   end
  
   if rooted then
      return "/"..table.concat( cleantab, "/" )
   end
   return table.concat( cleantab, "/" )
end
--ZFUNC-abspath-v3
local function abspath( path ) --> abs
   if isabsolute( path ) then
      return normpath( path )
   end
   return normpath( joinpath{ currentdir(), path } )
end
--ZFUNC-relativepath-v2
local function relativepath( from, to ) --> path
   from = abspath( from )
   to = abspath( to )
   if from == to then return "." end
   local fromtab = splitpath( normpath( from ) )
   local totab = splitpath( normpath( to ) )
   local f = 1
   local t = 1
   while f <= #fromtab and
         t <= #totab and
         fromtab[ f ] == totab[ t ] do
      f = f+1
      t = t+1
   end
   local pathtab = {}
   for i = f, #fromtab do
      table.insert( pathtab, ".." )
   end
   for i = t, #totab do
      table.insert( pathtab, totab[ i ] )
   end
   if #pathtab == 0 then return "." end
   return table.concat( pathtab, "/" )
end
return relativepath
end)()
--ZFUNC-startswith-v1
local function startswith( str, prefix ) --> res
   return string.sub( str, 1, string.len( prefix ) ) == prefix
end
--ZFUNC-writefile-v1
local function writefile( filename, ... ) --> res, err
   local f, err = io.open( filename, "w" )
   if err then return nil, err end
   local wres, err = f:write( ... )
   if err then return nil, err end
   return f:close()
end
--------------------------------------------------------------------------------
--LuaZDF-end
--------------------------------------------------------------------------------

local doctree = require( joinpath{ dirname( arg[0] ), "doctree" } )

local function logln( str, ... )
   return io.stdout:write( str:format( ... ), "\n" )
end
local function errfln( str, ... )
   return io.stderr:write( "Error: ", str:format( ... ), "\n" )
end
local function errexit( ... )
   if ... then
      errfln( ... )
   end
   os.exit( 1 )
end

local function cmdexec( cmdtab )
   local cmdline = table.concat( cmdtab, " " )
   logln( "Execute: %s", cmdline )
   local exit, signal, stdout, stderr = capexec( cmdline )
   if not exit then
      errfln( "Problems  with: %q", cmdline )
      errexit( stderr )
   end
   return stdout
end

local function adoctohtml( adocfile, rootdir ) --> html
   local adocdir = dirname( adocfile )

   local cmd = { "asciidoctor" }
   append( cmd, "-a", "idprefix=''" )
   append( cmd, "--backend", "html5" )
   append( cmd, "--no-header-footer" )
   append( cmd, "--out-file", "-" )
   append( cmd, "--attribute=source-highlighter=coderay" )
   append( cmd, "--attribute=rootdir="..relativepath( adocdir, rootdir ) )
   append( cmd, "--attribute=testroot="..relativepath( adocdir, joinpath{ rootdir, "test" } ) )
   append( cmd, "--attribute=docroot="..relativepath( adocdir, joinpath{ rootdir, "doc" } ) )
   append( cmd, adocfile )
   return cmdexec( cmd )
end

local function gen_adoc_id( entry ) --> id
   local id = rmsuffix( entry, "_" )
   id = string.lower( id )
   id = string.gsub( id, " ", "_" )
   return id
end

local function sidebarHeader( level, link ) --> html
   if level == 1 then
      return '<h1>'..link..'</h1>'
   elseif level == 2 then
      return '<h2>'..link..'</h2>'
   elseif level == 3 then
      return '<h3>'..link..'</h3>'
   elseif level == 4 then
      return '<h4>'..link..'</h4>'
   end
end

local function ahref( text, dest ) --> html
   return '<a href="'..dest..'">'..text..'</a>'
end

local function logodiv( path ) --> html
   local img = '<img src="'..path..'" alt="clingo-logo.svg">'
   return '<div id="logo-area">'..ahref( img, "https://code.aiq.dk/clingo/" )..'</div>'
end

local function tochtml( adoc, logopath ) --> html
   local lines, err = readlines( adoc )
   if err then
      errexit( "not able to read file: %s", err )
   end

   local html = {}
   table.insert( html, logodiv( logopath ) );
   for _, line in pairs( lines ) do
      if startswith( line, "=" ) then
         local linelevel, i = string.find( line, "=[^=]" )

         local entry = string.sub( line, i+1, -1 )
         local idval = entry
         if string.find( idval, " " ) then
            idval = gen_adoc_id( entry )
         end

         local link = ahref( entry, "#"..idval )
         if linelevel == 1 then
            link = ahref( entry, "" )
         end

         table.insert( html, sidebarHeader( linelevel, link ) )
      end
   end

   return table.concat( html, "\n" )
end

local function findroots() --> clingodir, docdir
   local clingodir = findup( currentdir(), "clingo", "directory" )
   if not clingodir then
      errexit( "Not able to find clingo directory" )
   end

   local docdir = joinpath{ clingodir, "doc" }
   if not isdir( docdir ) then
      errexit( "No doc directory in clingo directory" )
   end

   return clingodir, docdir
end

local function filestr( path ) --> str
   logln( "read %q", path )
   local str, err = readfile( path )
   if err then
      errexit( "Not able to read %q", path )
   end
   return str
end

local function getfilter( args ) --> filter
   if not args[1] then
      return function( name ) return true end
   else
      local set = buildset( arg )
      set[ args[0] ] = nil
      return function( name ) return set[ name ] end
   end
end

local function linktreehtml( from, doctree, parent, depth ) --> { html }
   local res = {}
   parent = parent or ""
   depth = depth or 1
   local keyValues = keys( doctree )
   table.sort( keyValues )
   for _,k in ipairs( keyValues ) do
      local val = doctree[ k ]
      if type( val ) == "table" then
         append( res, sidebarHeader( depth, k ) )
         appendall( res, linktreehtml( from, val, parent..k.."/", depth+1 ) )
      else
         val = rmsuffix( val, ".adoc" )
         local htmldest = relativepath( from, parent..val..".html" )
         local link = ahref( val, htmldest )
         append( res, sidebarHeader( depth, link ) )
      end
   end
   return res
end

--------------------------------------------------------------------------------

local clingodir, docdir = findroots()
local pagegen = mint( filestr( joinpath{ docdir, "clingo", "_assets", "page.htm" } ) )
local csspath = joinpath{ docdir, "clingo", "_assets", "solarized.css" }
local logopath = joinpath{ docdir, "clingo", "_assets", "clingo-logo.svg" }

local function writehtml( name, docfile, fromdir, destfile )
   local page = pagegen{
      TITLE = name,
      CSSFILE = relativepath( dirname( destfile ), csspath ),
      TOC = tochtml( docfile, relativepath( dirname( destfile ), logopath ) ),
      LINKS = table.concat( linktreehtml( fromdir , doctree ) ),
      CONTENT = adoctohtml( docfile, clingodir )
   }
   logln( "writefile: "..destfile )
   writefile( destfile, page )
end

--------------------------------------------------------------------------------

local readme = clingodir.."/README.adoc"
local readmehtml = docdir.."/clingo/index.html"
writehtml( "README", readme, "clingo", readmehtml )

local docfiles = filelist( doctree, docdir )
local filter = getfilter( arg )
for _, docfile in ipairs( docfiles ) do

   local name = basename( docfile, ".adoc" )
   if filter( name ) then
      local fromdir = dirname( relativepath( docdir, docfile ) )
      local htmlfile = rmsuffix( docfile, ".adoc" )..".html"
      writehtml( name, docfile, fromdir, htmlfile )
   end
end
