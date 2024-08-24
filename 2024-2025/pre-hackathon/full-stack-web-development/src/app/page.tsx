import Link from "next/link";
import { Button } from "~/components/ui/button";
import { getServerAuthSession } from "~/server/auth";
import { api, HydrateClient } from "~/trpc/server";

export default async function Home() {
  const hello = await api.hello({ text: "from tRPC" });
  const session = await getServerAuthSession();

  return (
    <HydrateClient>
      <main>{hello.greeting}</main>
      <Link passHref href={session ? "/api/auth/signout" : "/api/auth/signin"}>
        <Button>{session ? "Sign out" : "Sign in"}</Button>
      </Link>
    </HydrateClient>
  );
}
