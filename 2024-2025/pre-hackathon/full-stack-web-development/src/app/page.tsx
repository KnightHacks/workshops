import Link from "next/link";
import { Button } from "~/components/ui/button";
import { getServerAuthSession } from "~/server/auth";
import { api, HydrateClient } from "~/trpc/server";
import { HandleEditor } from "./_components/handle-editor";
import { PostEditor } from "./_components/post-editor";
import { PostList } from "./_components/post-list";

export default async function Home() {
  const hello = await api.hello({ text: "from tRPC" });
  const session = await getServerAuthSession();

  return (
    <HydrateClient>
      <main className="p-4">
        <div className="mb-1.5">
          <div>
            {hello.greeting}. You are signed in as {session?.user.name}.
          </div>
          <Link
            passHref
            href={session ? "/api/auth/signout" : "/api/auth/signin"}
          >
            <Button className="mb-2">{session ? "Sign out" : "Sign in"}</Button>
          </Link>
        </div>
        {session && (
          <>
            <HandleEditor currentHandle={session.user.handle} />
            <PostEditor />
            <PostList userId={session.user.id} />
          </>
        )}
      </main>
    </HydrateClient>
  );
}
